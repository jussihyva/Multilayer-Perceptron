/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:37:31 by juhani            #+#    #+#             */
/*   Updated: 2022/01/10 17:36:08 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static size_t	get_influxdb_tag_key_value_pairs(
							const char *const special_chars,
							t_queue *const key_value_queue)
{
	size_t				length;
	t_key_value_pair	key_value_pair;
	char				*key_value_string;

	length = 0;
	key_value_pair.key = "Record_type";
	key_value_pair.key_type = E_STRING;
	key_value_pair.value = "Hyper";
	key_value_pair.value_type = E_STRING;
	length += influxdb_key_value_pair_string_create(&key_value_pair,
			special_chars, &key_value_string);
	ft_enqueue(key_value_queue, (void *)key_value_string);
	return (length);
}

static size_t	get_hyper_params_key_value_pairs(
							const t_hyper_params *const hyper_params,
							const char *const special_chars,
							t_queue *const key_value_queue)
{
	size_t				length;
	t_key_value_pair	key_value_pair;
	char				*key_value_string;

	length = 0;
	key_value_pair.key = "learning_rate";
	key_value_pair.key_type = E_STRING;
	key_value_pair.value = (void *)&hyper_params->learning_rate;
	key_value_pair.value_type = E_DOUBLE;
	length += influxdb_key_value_pair_string_create(&key_value_pair,
			special_chars, &key_value_string);
	ft_enqueue(key_value_queue, (void *)key_value_string);
	key_value_pair.key = "percentage";
	key_value_pair.key_type = E_STRING;
	key_value_pair.value = (void *)&hyper_params->split_order.extra_info;
	key_value_pair.value_type = E_SIZE_T;
	length += influxdb_key_value_pair_string_create(&key_value_pair,
			special_chars, &key_value_string);
	ft_enqueue(key_value_queue, (void *)key_value_string);
	return (length);
}

void	send_hyper_params_to_database(
							const t_tcp_connection *const influxdb_connection,
							const t_hyper_params *const hyper_params)
{
	t_influxdb_elem		influxdb_elem;
	char				*line;
	size_t				len;
	t_queue				*key_value_queue;

	key_value_queue = ft_queue_init();
	len = 0;
	influxdb_elem.measurement = ft_strdup("");
	get_measurement_value("dataset_train", key_value_queue);
	get_influxdb_tag_key_value_pairs(SPECIAL_CHARS_INFLUXDB_TAGS,
		key_value_queue);
	len += influxdb_elem_string_create(&influxdb_elem.tag_set,
			key_value_queue);
	get_hyper_params_key_value_pairs(hyper_params,
		SPECIAL_CHARS_INFLUXDB_FIELDS, key_value_queue);
	len += influxdb_elem_string_create(&influxdb_elem.field_set,
			key_value_queue);
	len += influxdb_timestamp_set(&influxdb_elem.timestamp);
	line = ft_strdup("");
	influxdb_line_extend(&influxdb_elem, len, &line);
	influxdb_elem_remove(&influxdb_elem);
	ft_influxdb_write(influxdb_connection, line, NULL, 1);
	ft_strdel((char **)&line);
	ft_queue_remove(&key_value_queue);
	return ;
}
