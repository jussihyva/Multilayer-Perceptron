/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_iteration_result_to_database.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:35:55 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/17 17:15:57 by jkauppi          ###   ########.fr       */
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
							t_influxdb_elem *const tags_elem)
{
	t_queue				*string_queue;
	const char			*tag;
	const char			*value;

	tag = ft_strdup("Record_type");
	value = ft_strdup("Cost");
	string_queue = ft_queue_init();
	tags_elem->length = 0;
	tags_elem->length++;
	ft_enqueue(string_queue, ft_strdup(","));
	tags_elem->length += ft_strlen(tag);
	ft_enqueue(string_queue, (void *)tag);
	tags_elem->length++;
	ft_enqueue(string_queue, ft_strdup("="));
	tags_elem->length += ft_strlen(value);
	ft_enqueue(string_queue, (void *)value);
	tags_elem->string = ft_strcat_queue(string_queue, tags_elem->length);
	ft_queue_remove(&string_queue);
	return (tags_elem->length);
}

static size_t	influxdb_fields_add(
							t_influxdb_elem *const fields_elem,
							const size_t iter_cnt,
							const t_vector *vector)
{
	char				*string;
	t_queue				*string_queue;
	size_t				i;
	char				string_for_values[100];

	fields_elem->length = 0;
	string_queue = ft_queue_init();
	ft_sprintf(string_for_values, "iter=%u", iter_cnt);
	fields_elem->length += ft_strlen(string_for_values);
	ft_enqueue(string_queue, ft_strdup(string_for_values));
	i = -1;
	while (++i < vector->size)
	{
		fields_elem->length++;
		ft_enqueue(string_queue, ft_strdup(","));
		ft_sprintf(string_for_values, "%d", i);
		fields_elem->length += ft_strlen(string_for_values);
		ft_enqueue(string_queue, ft_strdup(string_for_values));
		fields_elem->length++;
		ft_enqueue(string_queue, ft_strdup("="));
		ft_sprintf(string_for_values, "%f", ((double *)vector->data)[i]);
		string = backslash_chars_add(SPECIAL_CHARS_INFLUXDB_FIELDS,
				string_for_values);
		fields_elem->length += ft_strlen(string);
		ft_enqueue(string_queue, string);
	}
	fields_elem->string = ft_strcat_queue(string_queue, fields_elem->length);
	ft_queue_remove(&string_queue);
	return (fields_elem->length);
}

void	send_iteration_result_to_database(
							const t_grad_descent_attr *const grad_descent_attr)
{
	t_influxdb_elem		*influxdb_elems;
	const char			*influxdb_string;
	size_t				total_len;

	if (grad_descent_attr->influxdb_connection)
	{
		influxdb_elems = ft_memalloc(sizeof(*influxdb_elems)
				* NUM_INFLUXDB_ELEMENTS);
		total_len = 0;
		total_len += influxdb_measurement_add(&influxdb_elems[E_MEASUREMENT],
				"dataset_train");
		total_len += influxdb_tags_add(&influxdb_elems[E_TAGS]);
		total_len += influxdb_fields_add(&influxdb_elems[E_FIELDS],
				grad_descent_attr->iter_cnt, grad_descent_attr->cost);
		total_len += influxdb_timestamp_add(&influxdb_elems[E_TIMESTAMP]);
		influxdb_string = elements_merge(influxdb_elems, total_len);
		influxdb_element_remove(&influxdb_elems);
		ft_influxdb_write(grad_descent_attr->influxdb_connection,
			influxdb_string, NULL, 1);
		ft_strdel((char **)&influxdb_string);
	}
	else
		FT_LOG_DEBUG("Cost value is not sent to influxdb");
	return ;
}
