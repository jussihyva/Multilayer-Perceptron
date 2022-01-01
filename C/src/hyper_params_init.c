/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper_params_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 13:26:53 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/01 17:04:07 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static t_bool	read_and_validate(
							const char *string,
							const t_data_type data_type,
							void *value)
{
	t_bool		validation_result;
	char		*endptr;

	validation_result = E_TRUE;
	if (data_type == E_SIZE_T)
	{
		errno = 0;
		*(size_t *)value = (size_t)ft_strtoi(string, &endptr, 10);
		if (errno != 0 || *endptr != '\0')
			validation_result = E_FALSE;
	}
	else
		validation_result = E_FALSE;
	return (validation_result);
}

static size_t	get_number_of_layers(const t_file_attr *const file_attr)
{
	size_t				num_of_layers;
	const char *const	*row;

	row = file_attr->row_array[0];
	if (!read_and_validate(row[0], E_SIZE_T, &num_of_layers))
		FT_LOG_ERROR("Contnet of file %s is not valid.",
			file_attr->file_path);
	return (num_of_layers);
}

static size_t	*get_number_of_nodes(
							const t_file_attr *const file_attr,
							const size_t num_of_layers)
{
	size_t				*num_of_nodes;
	const char *const	*row;
	size_t				num_of_hidden_layers;
	size_t				layer_id;
	size_t				row_id;

	num_of_hidden_layers = num_of_layers - 2;
	num_of_nodes = ft_memalloc(sizeof(*num_of_nodes) * num_of_layers);
	layer_id = 0;
	while (++layer_id < num_of_layers - 1)
	{
		row_id = layer_id;
		row = file_attr->row_array[row_id];
		if (!read_and_validate(row[0], E_SIZE_T, &num_of_nodes[layer_id]))
			FT_LOG_ERROR("Contnet of file %s is not valid.",
				file_attr->file_path);
	}
	return (num_of_nodes);
}

static t_weight_bias	*get_bias_weight_init_values(
							const t_file_attr *const file_attr,
							const size_t num_of_layers,
							const size_t *num_of_nodes)
{
	t_weight_bias		*bias_weight_init_values;
	t_size_2d			i;
	size_t				row_id;
	size_t				layer_id;
	const char *const	*row;
	double				**weight_table;
	double				*bias_data;

	row_id = num_of_layers - 2;
	layer_id = 1;
	bias_weight_init_values = ft_memalloc(sizeof(*bias_weight_init_values)
			* num_of_layers);
	while (layer_id < num_of_layers)
	{
		bias_weight_init_values[layer_id].bias
			= ml_vector_create(num_of_nodes[layer_id]);
		bias_weight_init_values[layer_id].weight
			= ml_matrix_create(num_of_nodes[layer_id],
				num_of_nodes[layer_id - 1]);
		row = file_attr->row_array[row_id];
		i.rows = 0;
		i.cols = 0;
		bias_data = (double *)bias_weight_init_values[layer_id].bias->data;
		read_and_validate(row[i.cols], E_DOUBLE, &bias_data[i.rows]);
		weight_table = (double **)bias_weight_init_values[layer_id].weight->table;
		while (++i.cols < num_of_nodes[layer_id])
			read_and_validate(row[i.cols], E_DOUBLE, &weight_table[i.rows][i.cols]);
		row_id++;
		layer_id++;
	}
	return (bias_weight_init_values);
}

t_hyper_params	*hyper_params_init(
						const char *const weight_bias_file,
						const t_hyper_params *const input_hyper_params)
{
	t_hyper_params	*hyper_params;
	t_file_attr		*file_attr;

	hyper_params = ft_memalloc(sizeof(*hyper_params));
	file_attr = ft_read_file(weight_bias_file, E_CSV);
	hyper_params->num_of_layers = get_number_of_layers(file_attr);
	hyper_params->num_of_nodes = get_number_of_nodes(file_attr,
			hyper_params->num_of_layers);
	hyper_params->bias_weight_init_values
		= get_bias_weight_init_values(file_attr,
			hyper_params->num_of_layers, hyper_params->num_of_nodes);
	hyper_params->dataset_split_order = input_hyper_params->dataset_split_order;
	hyper_params->epochs = input_hyper_params->epochs;
	hyper_params->learning_rate = input_hyper_params->learning_rate;
	return (hyper_params);
}
