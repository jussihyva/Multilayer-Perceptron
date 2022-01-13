/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weight.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:34:47 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/13 12:36:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	weight_tag_set_name_value_queue_init(
									const t_hyper_params *const hyper_params,
									const size_t layer_id,
									const size_t node_id,
									t_queue *const key_value_queue)
{
	const char		*name_value_string;
	char			value_string[1000];
	size_t			node_number;

	node_number = node_id + 1;
	name_value_string = ft_strdup("Record_type=Weight");
	ft_enqueue(key_value_queue, (void *)name_value_string);
	ft_sprintf(value_string, "%f", hyper_params->learning_rate);
	name_value_string = ft_strjoin("LearningRate=", value_string);
	ft_enqueue(key_value_queue, (void *)name_value_string);
	ft_sprintf(value_string, "%lu", layer_id);
	name_value_string = ft_strjoin("LayerId=", value_string);
	ft_enqueue(key_value_queue, (void *)name_value_string);
	ft_sprintf(value_string, "%lu", node_number);
	name_value_string = ft_strjoin("Node=", value_string);
	ft_enqueue(key_value_queue, (void *)name_value_string);
	return ;
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

static size_t	get_weight_key_value_pairs(
						const t_matrix *const weight,
						const size_t row_id,
						const char *const special_chars,
						t_queue *const key_value_queue)
{
	size_t				length;
	size_t				col_id;
	double				*weight_row;
	char				*key_value_string;
	t_key_value_pair	key_value_pair;

	length = 0;
	key_value_pair.key_type = E_SIZE_T;
	key_value_pair.value_type = E_DOUBLE;
	weight_row = (double *)weight->table[row_id];
	col_id = -1;
	while (++col_id < weight->size.cols)
	{
		key_value_pair.key = (void *)&col_id;
		key_value_pair.value = (void *)&weight_row[col_id];
		length += influxdb_key_value_pair_string_create(&key_value_pair,
				special_chars, &key_value_string);
		ft_enqueue(key_value_queue, (void *)key_value_string);
	}
	return (length);
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

	key_value_queue = ft_queue_init();
	i = -1;
	while (++i < weight->size.rows)
	{
		influxdb_elem.measurement = ft_strdup("");
		get_measurement_value("dataset_train", key_value_queue);
		weight_tag_set_name_value_queue_init(hyper_params, layer_id,
			i, key_value_queue);
		len = influxdb_elem_string_create(&influxdb_elem.tag_set,
				key_value_queue);
		get_weight_key_value_pairs(weight, i, SPECIAL_CHARS_INFLUXDB_FIELDS,
			key_value_queue);
		len += influxdb_elem_string_create(&influxdb_elem.field_set,
				key_value_queue);
		len += influxdb_timestamp_set(&influxdb_elem.timestamp);
		influxdb_line_extend(&influxdb_elem, len, line);
		influxdb_elem_remove(&influxdb_elem);
	}
	ft_queue_remove(&key_value_queue);
	return ;
}
