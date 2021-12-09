/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bias.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:58:20 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/09 18:42:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static t_queue	*bias_tag_set_name_value_queue_init(
									const t_hyper_params *const hyper_params,
									const size_t layer_id)
{
	t_queue			*name_value_queue;
	const char		*name_value_string;
	char			value_string[1000];

	name_value_queue = ft_queue_init();
	name_value_string = ft_strdup("Record_type=Bias");
	ft_enqueue(name_value_queue, (void *)name_value_string);
	ft_sprintf(value_string, "%f", hyper_params->learning_rate);
	name_value_string = ft_strjoin("LearningRate=", value_string);
	ft_enqueue(name_value_queue, (void *)name_value_string);
	ft_sprintf(value_string, "%d", layer_id);
	name_value_string = ft_strjoin("LayerId=", value_string);
	ft_enqueue(name_value_queue, (void *)name_value_string);
	return (name_value_queue);
}

void	send_bias_values_to_database(
								const size_t layer_id,
								const t_vector *const bias,
								const t_hyper_params *const hyper_params)
{
	t_influxdb_line			influxdb_line;
	const char				*line;
	size_t					total_len;
	size_t					num_of_nodes;
	const t_tcp_connection	*influxdb_connection;
	t_queue					*name_value_queue;

	influxdb_connection = get_database_connection();
	if (influxdb_connection)
	{
		line = ft_strdup("");
		num_of_nodes = g_layer_attrs[layer_id].nodes;
		total_len = 0;
		total_len += influxdb_measurement(&influxdb_line.measurement,
				"dataset_train");
		name_value_queue = bias_tag_set_name_value_queue_init(hyper_params,
				layer_id);
		total_len += influxdb_tag_set(&influxdb_line.tag_set, name_value_queue);
		total_len += influxdb_field_set(&influxdb_line.field_set, bias->data,
				bias->size);
		total_len += influxdb_timestamp(&influxdb_line.timestamp);
		influxdb_line_merge(&influxdb_line, total_len, &line);
		influxdb_line_remove(&influxdb_line);
		ft_influxdb_write(influxdb_connection, line, NULL, 1);
		ft_strdel((char **)&line);
		ft_queue_remove(&name_value_queue);
	}
	else
		FT_LOG_DEBUG("Cost value is not sent to influxdb");
	return ;
}

void	bias_update(const size_t layer_id, const t_vector *const bias,
				const t_vector *const d_bias, const double learning_rate)
{
	size_t			i;
	size_t			num_of_nodes;

	num_of_nodes = g_layer_attrs[layer_id].nodes;
	i = -1;
	while (++i < num_of_nodes)
		((double *)bias->data)[i]
			-= learning_rate * ((double *)d_bias->data)[i];
	return ;
}
