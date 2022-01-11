/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_iteration_result_to_database.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:35:55 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/11 12:22:55 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static size_t	add_dataset(
						const size_t dataset,
						const char *const special_chars,
						t_queue *const key_value_queue)
{
	t_key_value_pair	key_value_pair;
	char				*key_value_string;
	size_t				length;

	length = 0;
	key_value_pair.key = "Dataset";
	key_value_pair.key_type = E_STRING;
	key_value_pair.value = (void *)&dataset;
	key_value_pair.value_type = E_SIZE_T;
	length += influxdb_key_value_pair_string_create(&key_value_pair,
			special_chars, &key_value_string);
	ft_enqueue(key_value_queue, (void *)key_value_string);
	return (length);
}

static size_t	add_iter(
						const size_t iter,
						const char *const special_chars,
						t_queue *const key_value_queue)
{
	t_key_value_pair	key_value_pair;
	char				*key_value_string;
	size_t				length;

	length = 0;
	key_value_pair.key = "iter";
	key_value_pair.key_type = E_STRING;
	key_value_pair.value = (void *)&iter;
	key_value_pair.value_type = E_SIZE_T;
	length += influxdb_key_value_pair_string_create(&key_value_pair,
			special_chars, &key_value_string);
	ft_enqueue(key_value_queue, (void *)key_value_string);
	return (length);
}

static size_t	add_vector(
						const t_vector *const vector,
						const char *const special_chars,
						t_queue *const key_value_queue)
{
	size_t				length;
	size_t				i;
	char				*key_value_string;
	t_key_value_pair	key_value_pair;

	length = 0;
	key_value_pair.key_type = E_SIZE_T;
	key_value_pair.value_type = E_DOUBLE;
	i = -1;
	while (++i < vector->size)
	{
		key_value_pair.key = (void *)&i;
		key_value_pair.value = (void *)&((double *)vector->data)[i];
		length += influxdb_key_value_pair_string_create(&key_value_pair,
				special_chars, &key_value_string);
		ft_enqueue(key_value_queue, (void *)key_value_string);
	}
	return (length);
}

static char	*influxdb_elem_create(
						const t_vector *const cost,
						const size_t dataset,
						const size_t iter_cnt)
{
	t_influxdb_elem		influxdb_elem;
	t_queue				*key_value_queue;
	size_t				len;
	char				*line;

	key_value_queue = ft_queue_init();
	len = 0;
	influxdb_elem.measurement = ft_strdup("");
	get_measurement_value("dataset_train", key_value_queue);
	add_record_type("Cost", SPECIAL_CHARS_INFLUXDB_TAGS, key_value_queue);
	add_dataset(dataset, SPECIAL_CHARS_INFLUXDB_TAGS, key_value_queue);
	len += influxdb_elem_string_create(&influxdb_elem.tag_set,
			key_value_queue);
	add_iter(iter_cnt, SPECIAL_CHARS_INFLUXDB_FIELDS, key_value_queue);
	add_vector(cost, SPECIAL_CHARS_INFLUXDB_FIELDS, key_value_queue);
	len += influxdb_elem_string_create(&influxdb_elem.field_set,
			key_value_queue);
	len += influxdb_timestamp_set(&influxdb_elem.timestamp);
	line = ft_strdup("");
	influxdb_line_extend(&influxdb_elem, len, &line);
	influxdb_elem_remove(&influxdb_elem);
	ft_queue_remove(&key_value_queue);
	return (line);
}

void	send_iteration_result_to_database(
							const t_tcp_connection *const influxdb_connection,
							const t_layer_output *const layer_output,
							const size_t iter_cnt)
{
	char				*line;
	size_t				i;

	if (influxdb_connection)
	{
		i = -1;
		while (++i < NUM_OF_DATASETS)
		{
			line = influxdb_elem_create(layer_output->cost[i], i, iter_cnt);
			ft_influxdb_write(influxdb_connection, line, NULL, 1);
			ft_strdel((char **)&line);
		}
	}
	else
		FT_LOG_DEBUG("Cost value is not sent to influxdb");
	return ;
}
