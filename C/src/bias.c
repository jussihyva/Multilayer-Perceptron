/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bias.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:58:20 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/10 12:03:43 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	bias_tag_set_name_value_queue_init(
									const t_hyper_params *const hyper_params,
									const size_t layer_id,
									t_queue *const key_value_queue)
{
	const char		*name_value_string;
	char			value_string[1000];

	name_value_string = ft_strdup("Record_type=Bias");
	ft_enqueue(key_value_queue, (void *)name_value_string);
	ft_sprintf(value_string, "%f", hyper_params->learning_rate);
	name_value_string = ft_strjoin("LearningRate=", value_string);
	ft_enqueue(key_value_queue, (void *)name_value_string);
	ft_sprintf(value_string, "%d", layer_id);
	name_value_string = ft_strjoin("LayerId=", value_string);
	ft_enqueue(key_value_queue, (void *)name_value_string);
	return ;
}

void	send_layer_stat_to_database(
							const t_tcp_connection	*influxdb_connection,
							void *const *const layers,
							const t_layer_type *const layer_types,
							const size_t num_of_layers)
{
	const char				*line;
	size_t					layer_id;

	layer_id = -1;
	while (++layer_id < num_of_layers)
	{
		if (layer_types[layer_id] == E_LAYER_INPUT)
			continue ;
		else if (layer_types[layer_id] == E_LAYER_HIDDEN)
			line = get_layer_stat_hidden(layers[layer_id], layer_id);
		else if (layer_types[layer_id] == E_LAYER_OUTPUT)
			line = get_layer_stat_output(layers[layer_id], layer_id);
		else
			FT_LOG_FATAL("Unsupported layer type: %u",
				layer_types[layer_id]);
		ft_influxdb_write(influxdb_connection, line, NULL, 1);
		ft_strdel((char **)&line);
	}
	return ;
}

void	bias_update(
				const size_t layer_id,
				const t_vector *const bias,
				const t_vector *const d_bias,
				const t_hyper_params *const hyper_params)
{
	size_t			i;

	i = -1;
	while (++i < hyper_params->num_of_nodes[layer_id])
		((double *)bias->data)[i]
			-= hyper_params->learning_rate * ((double *)d_bias->data)[i];
	return ;
}

size_t	get_bias_key_value_pairs(
						const t_vector *const bias,
						const char *const special_chars,
						t_queue *const key_value_queue)
{
	size_t				length;
	size_t				i;
	double				*bias_data;
	char				*key_value_string;
	t_key_value_pair	key_value_pair;

	length = 0;
	key_value_pair.key_type = E_SIZE_T;
	key_value_pair.value_type = E_DOUBLE;
	bias_data = (double *)bias->data;
	i = -1;
	while (++i < bias->size)
	{
		key_value_pair.key = (void *)&i;
		key_value_pair.value = (void *)&bias_data[i];
		length += influxdb_key_value_pair_string_create(&key_value_pair,
				special_chars, &key_value_string);
		ft_enqueue(key_value_queue, (void *)key_value_string);
	}
	return (length);
}

void	bias_stat_add(
					char **const line,
					const t_vector *const bias,
					const t_hyper_params *const hyper_params,
					const size_t layer_id)
{
	t_influxdb_elem		influxdb_elem;
	size_t				len;
	t_queue				*key_value_queue;

	len = 0;
	len += influxdb_measurement(&influxdb_elem.measurement, "dataset_train");
	key_value_queue = ft_queue_init();
	bias_tag_set_name_value_queue_init(hyper_params, layer_id, key_value_queue);
	len += influxdb_tag_set(&influxdb_elem.tag_set, key_value_queue);
	get_bias_key_value_pairs(bias, SPECIAL_CHARS_INFLUXDB_FIELDS,
		key_value_queue);
	len += influxdb_field_set(&influxdb_elem.field_set, key_value_queue);
	len += influxdb_timestamp_set(&influxdb_elem.timestamp);
	ft_queue_remove(&key_value_queue);
	influxdb_line_extend(&influxdb_elem, len, line);
	influxdb_elem_remove(&influxdb_elem);
	return ;
}
