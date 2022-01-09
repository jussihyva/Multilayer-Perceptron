/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weight.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:34:47 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/09 11:21:17 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static t_queue	*weight_tag_set_name_value_queue_init(
									const t_hyper_params *const hyper_params,
									const size_t layer_id,
									const size_t node_id)
{
	t_queue			*name_value_queue;
	const char		*name_value_string;
	char			value_string[1000];
	size_t			node_number;

	node_number = node_id + 1;
	name_value_queue = ft_queue_init();
	name_value_string = ft_strdup("Record_type=Weight");
	ft_enqueue(name_value_queue, (void *)name_value_string);
	ft_sprintf(value_string, "%f", hyper_params->learning_rate);
	name_value_string = ft_strjoin("LearningRate=", value_string);
	ft_enqueue(name_value_queue, (void *)name_value_string);
	ft_sprintf(value_string, "%lu", layer_id);
	name_value_string = ft_strjoin("LayerId=", value_string);
	ft_enqueue(name_value_queue, (void *)name_value_string);
	ft_sprintf(value_string, "%lu", node_number);
	name_value_string = ft_strjoin("Node=", value_string);
	ft_enqueue(name_value_queue, (void *)name_value_string);
	return (name_value_queue);
}

void	weight_update(
				const size_t layer_id,
				const t_matrix *const weight,
				const t_matrix *const d_weight,
				const t_hyper_params *const hyper_params)
{
	t_size_2d	i;
	size_t		total_size;
	size_t		num_of_activation_inputs;
	size_t		prev_layer_id;

	prev_layer_id = layer_id - 1;
	num_of_activation_inputs = hyper_params->num_of_nodes[prev_layer_id];
	total_size = hyper_params->num_of_nodes[layer_id]
		* num_of_activation_inputs;
	i.rows = -1;
	while (++i.rows < hyper_params->num_of_nodes[layer_id])
	{
		i.cols = -1;
		while (++i.cols < num_of_activation_inputs)
			((double **)weight->table)[i.rows][i.cols]
				-= hyper_params->learning_rate
				* ((double **)d_weight->table)[i.rows][i.cols];
	}
	return ;
}

void	weight_stat_add(
					char **const line,
					const t_matrix *const weight,
					const t_hyper_params *const hyper_params,
					const size_t layer_id)
{
	t_influxdb_elem		influxdb_elem;
	size_t				len;
	t_queue				*key_value_queue;
	size_t				i;

	i = -1;
	while (++i < weight->size.rows)
	{
		len = 0;
		len += influxdb_measurement(&influxdb_elem.measurement,
				"dataset_train");
		key_value_queue
			= weight_tag_set_name_value_queue_init(hyper_params, layer_id,
				i);
		len += influxdb_tag_set(&influxdb_elem.tag_set, key_value_queue);
		ft_queue_remove(&key_value_queue);
		len += influxdb_field_set(&influxdb_elem.field_set,
				weight->table[i], weight->size.cols);
		len += influxdb_timestamp_set(&influxdb_elem.timestamp);
		influxdb_line_extend(&influxdb_elem, len, line);
		influxdb_elem_remove(&influxdb_elem);
	}
	return ;
}
