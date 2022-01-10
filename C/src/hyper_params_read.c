/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper_params_read.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 08:21:42 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/11 00:19:04 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static size_t	get_number_of_layers(const t_file_attr *const file_attr)
{
	size_t				num_of_layers;
	const char *const	*row;

	row = file_attr->row_array[0];
	if (!string_convert_and_validate(row[0], E_SIZE_T, &num_of_layers))
		FT_LOG_ERROR("Contnet of file %s is not valid.",
			file_attr->file_path);
	return (num_of_layers);
}

static size_t	*get_number_of_nodes(
							const t_file_attr *const file_attr,
							const size_t num_of_layers,
							const size_t num_of_input_functions,
							const size_t num_of_output_functions)
{
	size_t				*num_of_nodes;
	const char *const	*row;
	size_t				num_of_hidden_layers;
	size_t				layer_id;
	size_t				row_id;

	num_of_hidden_layers = num_of_layers - 2;
	num_of_nodes = ft_memalloc(sizeof(*num_of_nodes) * num_of_layers);
	layer_id = 0;
	num_of_nodes[layer_id] = num_of_input_functions;
	while (++layer_id < num_of_layers - 1)
	{
		row_id = layer_id;
		row = file_attr->row_array[row_id];
		if (!string_convert_and_validate(row[0], E_SIZE_T,
				&num_of_nodes[layer_id]))
			FT_LOG_ERROR("Contnet of file %s is not valid.",
				file_attr->file_path);
	}
	num_of_nodes[layer_id] = num_of_output_functions;
	return (num_of_nodes);
}

static t_weight_bias	*get_bias_weight_init_values(
							const t_file_attr *const file_attr,
							const size_t num_of_layers,
							const size_t *num_of_nodes)
{
	t_weight_bias		*bias_weight_init_values;
	t_size_2d			size;
	size_t				row_id;
	size_t				layer_id;
	t_weight_bias		*bias_weight;

	row_id = num_of_layers - 2 + 1;
	layer_id = 1;
	bias_weight_init_values = ft_memalloc(sizeof(*bias_weight_init_values)
			* num_of_layers);
	while (layer_id < num_of_layers)
	{
		bias_weight = &bias_weight_init_values[layer_id];
		bias_weight->bias = ml_vector_create(num_of_nodes[layer_id]);
		size.rows = num_of_nodes[layer_id];
		size.cols = num_of_nodes[layer_id - 1];
		bias_weight->weight = ml_matrix_create(size);
		bias_weight_values_read(bias_weight, file_attr->row_array, &row_id);
		layer_id++;
	}
	return (bias_weight_init_values);
}

void	get_hyper_params_from_file(
						const char *const weight_bias_file,
						const size_t num_of_input_functions,
						const size_t num_of_output_functions,
						t_hyper_params	*hyper_params)
{
	t_file_attr		*file_attr;

	file_attr = ft_read_file(weight_bias_file, E_CSV);
	hyper_params->num_of_layers = get_number_of_layers(file_attr);
	hyper_params->num_of_nodes = get_number_of_nodes(file_attr,
			hyper_params->num_of_layers, num_of_input_functions,
			num_of_output_functions);
	hyper_params->bias_weight_init_values
		= get_bias_weight_init_values(file_attr,
			hyper_params->num_of_layers, hyper_params->num_of_nodes);
	file_attr_remove(&file_attr);
	return ;
}
