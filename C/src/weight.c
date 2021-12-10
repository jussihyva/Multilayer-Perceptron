/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weight.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:34:47 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/10 14:43:09 by jkauppi          ###   ########.fr       */
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

void	send_weight_values_to_database(
								const size_t layer_id,
								const t_matrix *const weight,
								const t_hyper_params *const hyper_params)
{
	t_influxdb_line			influxdb_line;
	const char				*line;
	size_t					total_len;
	size_t					num_of_nodes;
	const t_tcp_connection	*influxdb_connection;
	t_queue					*name_value_queue;
	size_t					i;

	influxdb_connection = get_database_connection();
	if (influxdb_connection)
	{
		line = ft_strdup("");
		total_len = 0;
		num_of_nodes = g_layer_attrs[NUM_OF_LAYERS][layer_id].nodes;
		i = -1;
		while (++i < weight->size.rows)
		{
			total_len += influxdb_measurement(&influxdb_line.measurement,
					"dataset_train");
			name_value_queue = weight_tag_set_name_value_queue_init(hyper_params,
					layer_id, i);
			total_len += influxdb_tag_set(&influxdb_line.tag_set, name_value_queue);
			ft_queue_remove(&name_value_queue);
			total_len += influxdb_field_set(&influxdb_line.field_set,
					weight->table[i], weight->size.cols);
			total_len += influxdb_timestamp(&influxdb_line.timestamp);
			influxdb_line_merge(&influxdb_line, total_len, &line);
			influxdb_line_remove(&influxdb_line);
		}
		ft_influxdb_write(influxdb_connection, line, NULL, 1);
		ft_strdel((char **)&line);
	}
	else
		FT_LOG_DEBUG("Cost value is not sent to influxdb");
	return ;
}

void	weight_update(const size_t layer_id, const t_matrix *const weight,
				const t_matrix *const d_weight, const double learning_rate)
{
	t_size_2d	i;
	size_t		total_size;
	size_t		num_of_nodes;
	size_t		num_of_activation_inputs;
	size_t		prev_layer_id;

	prev_layer_id = layer_id - 1;
	num_of_nodes = g_layer_attrs[NUM_OF_LAYERS][layer_id].nodes;
	num_of_activation_inputs = g_layer_attrs[NUM_OF_LAYERS][prev_layer_id].nodes;
	total_size = num_of_nodes * num_of_activation_inputs;
	i.rows = -1;
	while (++i.rows < num_of_nodes)
	{
		i.cols = -1;
		while (++i.cols < num_of_activation_inputs)
			((double **)weight->table)[i.rows][i.cols] -= learning_rate
				* ((double **)d_weight->table)[i.rows][i.cols];
	}
	return ;
}

