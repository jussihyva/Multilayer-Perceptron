/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_softmax_result_to_database.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhani <juhani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:33:42 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/23 14:18:57 by juhani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static size_t	influxdb_timestamp_add(t_influxdb_elem *timestamp_elem)
{
	size_t		utc_time_ms;
	char		string[100];

	utc_time_ms = ft_gettime();
	ft_sprintf(string, "%lu", utc_time_ms);
	timestamp_elem->length = ft_strlen(string);
	timestamp_elem->string = ft_strdup(string);
	return (timestamp_elem->length);
}

static size_t	new_length_calculate(
					const char *special_chars,
					const char *const string)
{
	const char	*ptr;
	size_t		length;

	length = ft_strlen(string);
	ptr = string;
	while (*ptr)
	{
		if (ft_strchr(special_chars, *ptr))
			length++;
		ptr++;
	}
	return (length);
}

static char	*backslash_chars_add(
					const char *const special_chars,
					const char *const string)
{
	char			*new_string;
	const char		*ptr;
	size_t			new_length;
	size_t			i;

	new_length = new_length_calculate(special_chars, string);
	new_string = ft_strnew(new_length);
	i = 0;
	ptr = string;
	while (*ptr)
	{
		if (ft_strchr(special_chars, *ptr))
			new_string[i++] = '\\';
		new_string[i++] = *ptr;
		ptr++;
	}
	return (new_string);
}

static size_t	influxdb_measurement_add(
						t_influxdb_elem *const measurement_elem,
						const char *const measurement)
{
	measurement_elem->string
		= backslash_chars_add(SPECIAL_CHARS_INFLUXDB_MEASUREMENT, measurement);
	measurement_elem->length = ft_strlen(measurement_elem->string);
	return (measurement_elem->length);
}

static void	influxdb_element_remove(t_influxdb_elem **influxdb_elems)
{
	ft_strdel((char **)&(*influxdb_elems)[E_MEASUREMENT].string);
	ft_strdel((char **)&(*influxdb_elems)[E_TAGS].string);
	ft_strdel((char **)&(*influxdb_elems)[E_FIELDS].string);
	ft_strdel((char **)&(*influxdb_elems)[E_TIMESTAMP].string);
	ft_memdel((void **)influxdb_elems);
	return ;
}

static const char	*elements_merge(
						t_influxdb_elem *const influxdb_elems,
						size_t total_len)
{
	char		*influxdb_string;

	total_len += 2;
	influxdb_string = ft_strnew(sizeof(*influxdb_string) * total_len);
	ft_sprintf(influxdb_string, "%s%s %s %s",
		influxdb_elems[E_MEASUREMENT].string,
		influxdb_elems[E_TAGS].string,
		influxdb_elems[E_FIELDS].string,
		influxdb_elems[E_TIMESTAMP].string);
	if (ft_strlen(influxdb_string) != total_len)
		FT_LOG_WARN("Influxdb line: %lu <--> %lu", ft_strlen(influxdb_string),
			total_len);
	return (influxdb_string);
}

static size_t	influxdb_tags_add(
							t_influxdb_elem *const tags_elem,
							const char *const example_id)
{
	t_queue				*string_queue;
	const char			*tag_value_pair;

	string_queue = ft_queue_init();
	tags_elem->length = 0;
	tags_elem->length++;
	ft_enqueue(string_queue, ft_strdup(","));
	tag_value_pair = ft_strdup("Record_type=Softmax");
	tags_elem->length += ft_strlen(tag_value_pair);
	ft_enqueue(string_queue, (void *)tag_value_pair);
	tags_elem->length++;
	ft_enqueue(string_queue, ft_strdup(","));
	tag_value_pair = ft_strjoin("ExampleId=", example_id);
	tags_elem->length += ft_strlen(tag_value_pair);
	ft_enqueue(string_queue, (void *)tag_value_pair);
	tags_elem->string = ft_strcat_queue(string_queue, tags_elem->length);
	ft_queue_remove(&string_queue);
	return (tags_elem->length);
}

static size_t	influxdb_fields_add(
							t_influxdb_elem *const fields_elem,
							const t_matrix *matrix,
							const size_t col)
{
	t_queue				*string_queue;
	size_t				i;
	char				string[100];
	double				value;
	double				bigger_value;

	fields_elem->length = 0;
	string_queue = ft_queue_init();
	ft_sprintf(string, "ExampleId=%u", col);
	fields_elem->length += ft_strlen(string);
	ft_enqueue(string_queue, ft_strdup(string));
	bigger_value = DBL_MIN;
	i = -1;
	while (++i < matrix->size.rows)
	{
		fields_elem->length++;
		ft_enqueue(string_queue, ft_strdup(","));
		ft_sprintf(string, "%d", i);
		fields_elem->length += ft_strlen(string);
		ft_enqueue(string_queue, ft_strdup(string));
		fields_elem->length++;
		ft_enqueue(string_queue, ft_strdup("="));
		value = ((double **)matrix->table)[i][col];
		bigger_value = ft_max_double(bigger_value, value);
		ft_sprintf(string, "%f", value);
		fields_elem->length += ft_strlen(string);
		ft_enqueue(string_queue, ft_strdup(string));
	}
	fields_elem->length++;
	ft_enqueue(string_queue, ft_strdup(","));
	ft_sprintf(string, "BiggerValue=%f", bigger_value);
	fields_elem->length += ft_strlen(string);
	ft_enqueue(string_queue, ft_strdup(string));
	fields_elem->string = ft_strcat_queue(string_queue, fields_elem->length);
	ft_queue_remove(&string_queue);
	return (fields_elem->length);
}

void	send_softmax_result_to_database(
							const t_grad_descent_attr *const grad_descent_attr)
{
	t_influxdb_elem		*influxdb_elems;
	const char			*influxdb_string;
	const char			*example_id;
	size_t				total_len;
	t_size_2d			i;

	if (grad_descent_attr->influxdb_connection)
	{
		i.cols = -1;
		while (++i.cols < grad_descent_attr->softmax->size.cols)
		{
			influxdb_elems = ft_memalloc(sizeof(*influxdb_elems)
					* NUM_INFLUXDB_ELEMENTS);
			total_len = 0;
			total_len += influxdb_measurement_add(
					&influxdb_elems[E_MEASUREMENT], "dataset_train");
			example_id = ft_itoa(i.cols);
			total_len += influxdb_tags_add(&influxdb_elems[E_TAGS], example_id);
			ft_strdel((char **)&example_id);
			total_len += influxdb_fields_add(&influxdb_elems[E_FIELDS],
					grad_descent_attr->softmax, i.cols);
			total_len += influxdb_timestamp_add(&influxdb_elems[E_TIMESTAMP]);
			influxdb_string = elements_merge(influxdb_elems, total_len);
			influxdb_element_remove(&influxdb_elems);
			ft_influxdb_write(grad_descent_attr->influxdb_connection,
				influxdb_string, NULL, 1);
			ft_strdel((char **)&influxdb_string);
		}
	}
	else
		FT_LOG_DEBUG("Cost value is not sent to influxdb");
	return ;
}
