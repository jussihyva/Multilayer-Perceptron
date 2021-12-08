/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:39:54 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/08 20:33:48 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static size_t	count_special_chars(
					const char *special_chars,
					const char *const string)
{
	const char	*ptr;
	size_t		num_of_special_chars;

	num_of_special_chars = 0;
	ptr = string;
	while (*ptr)
	{
		if (ft_strchr(special_chars, *ptr))
			num_of_special_chars++;
		ptr++;
	}
	return (num_of_special_chars);
}

static char	*validate_influxdb_line_string(
					const char *const special_chars,
					const char *const string)
{
	char			*new_string;
	const char		*ptr;
	size_t			num_of_special_chars;
	size_t			i;

	num_of_special_chars = count_special_chars(special_chars, string);
	new_string = ft_strnew(ft_strlen(string) + num_of_special_chars);
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

size_t	influxdb_measurement(
						const char **const measurement,
						const char *const string)
{
	size_t		length;

	*measurement = validate_influxdb_line_string(
			SPECIAL_CHARS_INFLUXDB_MEASUREMENT, string);
	length = ft_strlen(*measurement);
	return (length);
}

void	influxdb_line_remove(t_influxdb_line *influxdb_line)
{
	ft_strdel((char **)&influxdb_line->measurement);
	ft_strdel((char **)&influxdb_line->tag_set);
	ft_strdel((char **)&influxdb_line->field_set);
	ft_strdel((char **)&influxdb_line->timestamp);
	return ;
}

const char	*influxdb_line_merge(
						const t_influxdb_line *const influxdb_line,
						size_t total_len)
{
	char		*line;

	total_len += 2;
	line = ft_strnew(sizeof(*line) * total_len);
	ft_sprintf(line, "%s%s %s %s",
		influxdb_line->measurement,
		influxdb_line->tag_set,
		influxdb_line->field_set,
		influxdb_line->timestamp);
	if (ft_strlen(line) != total_len)
		FT_LOG_WARN("Influxdb line: %lu <--> %lu", ft_strlen(line),
			total_len);
	return (line);
}

size_t	influxdb_tag_set(
					const char **const tag_set,
					t_queue *const name_value_queue)
{
	size_t			length;
	const char		*name_value_string;
	const char		*updated_string;

	*tag_set = ft_strdup("");
	while (!ft_is_queue_empty(name_value_queue))
	{
		updated_string = ft_strjoin(*tag_set, ",");
		ft_strdel((char **)tag_set);
		*tag_set = updated_string;
		name_value_string = (char *)ft_dequeue(name_value_queue);
		updated_string = ft_strjoin(*tag_set, name_value_string);
		ft_strdel((char **)&name_value_string);
		ft_strdel((char **)tag_set);
		*tag_set = updated_string;
	}
	length = ft_strlen(*tag_set);
	if (length <= 1)
	{
		ft_strdel((char **)tag_set);
		length = 0;
	}
	return (length);
}

static size_t	add(
					t_queue *string_queue,
					void *const value,
					t_influxdb_field_type influxdb_field_type,
					const char *const special_chars)
{
	size_t			length;
	char			value_to_string[100];
	const char		*validated_string;

	if (influxdb_field_type == E_DOUBLE)
		ft_sprintf(value_to_string, "%f", *(double *)value);
	else if (influxdb_field_type == E_STRING)
		ft_sprintf(value_to_string, "%s", (char *)value);
	else if (influxdb_field_type == E_SIZE_T)
		ft_sprintf(value_to_string, "%lu", *(size_t *)value);
	if (special_chars)
		validated_string = validate_influxdb_line_string(
				SPECIAL_CHARS_INFLUXDB_FIELDS, value_to_string);
	else
		validated_string = ft_strdup(value_to_string);
	length = ft_strlen(validated_string);
	ft_enqueue(string_queue, (void *)validated_string);
	return (length);
}

static size_t	add_name_value(
					t_queue *const string_queue,
					size_t i,
					double value)
{
	size_t			length;

	length = 0;
	length += add(string_queue, &i, E_SIZE_T,
			SPECIAL_CHARS_INFLUXDB_FIELDS);
	length += add(string_queue, &"=", E_STRING, NULL);
	length += add(string_queue, &value,
			E_DOUBLE, SPECIAL_CHARS_INFLUXDB_FIELDS);
	return (length);
}

size_t	influxdb_field_set(
							const char **const field_set,
							const t_vector *const vector,
							const t_matrix *const matrix)
{
	size_t			length;
	t_size_2d		i;
	t_queue			*string_queue;

	length = 0;
	string_queue = ft_queue_init();
	i.rows = -1;
	while (++i.rows < vector->size)
	{
		if (i.rows)
			length += add(string_queue, &",", E_STRING, NULL);
		length += add_name_value(string_queue, i.rows,
				((double *)vector->data)[i.rows]);
	}
	(void)matrix;
	*field_set = ft_strcat_queue(string_queue, length);
	ft_queue_remove(&string_queue);
	return (length);
}

size_t	influxdb_timestamp(const char **const timestamp)
{
	size_t		utc_time_ms;
	char		string[100];
	size_t		length;

	utc_time_ms = ft_gettime();
	ft_sprintf(string, "%lu", utc_time_ms);
	length = ft_strlen(string);
	*timestamp = ft_strdup(string);
	return (length);
}

