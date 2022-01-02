/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_iteration_result_to_database.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:35:55 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/02 21:10:15 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

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

static size_t	influxdb_tags_add(const char **const tags_set, const size_t dataset_type)
{
	t_queue		*string_queue;
	char		*tag_value_pair;
	size_t		length;

	string_queue = ft_queue_init();
	length = 0;
	length++;
	ft_enqueue(string_queue, ft_strdup(","));
	tag_value_pair = ft_strdup("Record_type=Cost");
	length += ft_strlen(tag_value_pair);
	ft_enqueue(string_queue, (void *)tag_value_pair);
	length++;
	ft_enqueue(string_queue, ft_strdup(","));
	tag_value_pair = ft_strnew(100);
	ft_sprintf(tag_value_pair, "Dataset=%lu", dataset_type);
	length += ft_strlen(tag_value_pair);
	ft_enqueue(string_queue, (void *)tag_value_pair);
	*tags_set = ft_strcat_queue(string_queue, length);
	ft_queue_remove(&string_queue);
	return (length);
}

static size_t	influxdb_fields_add(
							const char **const field_set,
							const size_t iter_cnt,
							const t_vector *vector)
{
	char				*string;
	t_queue				*string_queue;
	size_t				i;
	char				string_for_values[100];
	size_t				length;

	length = 0;
	string_queue = ft_queue_init();
	ft_sprintf(string_for_values, "iter=%u", iter_cnt);
	length += ft_strlen(string_for_values);
	ft_enqueue(string_queue, ft_strdup(string_for_values));
	i = -1;
	while (++i < vector->size)
	{
		length++;
		ft_enqueue(string_queue, ft_strdup(","));
		ft_sprintf(string_for_values, "%d", i);
		length += ft_strlen(string_for_values);
		ft_enqueue(string_queue, ft_strdup(string_for_values));
		length++;
		ft_enqueue(string_queue, ft_strdup("="));
		ft_sprintf(string_for_values, "%f", ((double *)vector->data)[i]);
		string = backslash_chars_add(SPECIAL_CHARS_INFLUXDB_FIELDS,
				string_for_values);
		length += ft_strlen(string);
		ft_enqueue(string_queue, string);
	}
	*field_set = ft_strcat_queue(string_queue, length);
	ft_queue_remove(&string_queue);
	return (length);
}

void	send_iteration_result_to_database(
							const t_tcp_connection *const influxdb_connection,
							const t_layer_output *const layer_output,
							const size_t iter_cnt)
{
	t_influxdb_line		influxdb_line;
	const char			*line;
	size_t				total_len;
	size_t				i;

	if (influxdb_connection)
	{
		i = -1;
		while (++i < NUM_OF_DATASETS)
		{
			total_len = 0;
			total_len += influxdb_measurement(&influxdb_line.measurement,
					"dataset_train");
			total_len += influxdb_tags_add(&influxdb_line.tag_set, i);
			total_len += influxdb_fields_add(&influxdb_line.field_set, iter_cnt,
					layer_output->cost[i]);
			total_len += influxdb_timestamp_add(&influxdb_line.timestamp);
			line = elements_merge(&influxdb_line, total_len);
			influxdb_element_remove(&influxdb_line);
			ft_influxdb_write(influxdb_connection, line, NULL, 1);
			ft_strdel((char **)&line);
		}
	}
	else
		FT_LOG_DEBUG("Cost value is not sent to influxdb");
	return ;
}
