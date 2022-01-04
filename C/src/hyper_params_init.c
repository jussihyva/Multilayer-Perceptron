/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper_params_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 13:26:53 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/04 12:48:29 by jkauppi          ###   ########.fr       */
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
	else if (data_type == E_DOUBLE)
	{
		errno = 0;
		*(double *)value = strtod(string, &endptr);
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
		if (!read_and_validate(row[0], E_SIZE_T, &num_of_nodes[layer_id]))
			FT_LOG_ERROR("Contnet of file %s is not valid.",
				file_attr->file_path);
	}
	num_of_nodes[layer_id] = num_of_output_functions;
	return (num_of_nodes);
}

static size_t	*get_number_of_nodes_default(const size_t num_of_layers)
{
	const t_layer_profile	*layer_profile;
	size_t					*num_of_nodes;
	size_t					i;

	num_of_nodes = ft_memalloc(sizeof(*num_of_nodes) * num_of_layers);
	layer_profile = g_layer_attrs[num_of_layers];
	i = -1;
	while (++i < num_of_layers)
		num_of_nodes[i] = layer_profile[i].nodes;
	return (num_of_nodes);
}

static t_activation_type	*get_activation_types(const size_t num_of_layers)
{
	const t_layer_profile	*layer_profile;
	t_activation_type		*activation_types;
	size_t					i;

	activation_types = ft_memalloc(sizeof(*activation_types) * num_of_layers);
	layer_profile = g_layer_attrs[num_of_layers];
	i = -1;
	while (++i < num_of_layers)
		activation_types[i] = layer_profile[i].activation_type;
	return (activation_types);
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
	const char *const	*row;
	double				**weight_table;
	double				*bias_data;

	row_id = num_of_layers - 2 + 1;
	layer_id = 1;
	bias_weight_init_values = ft_memalloc(sizeof(*bias_weight_init_values)
			* num_of_layers);
	while (layer_id < num_of_layers)
	{
		bias_weight_init_values[layer_id].bias
			= ml_vector_create(num_of_nodes[layer_id]);
		size.rows = num_of_nodes[layer_id];
		size.cols = num_of_nodes[layer_id - 1];
		bias_weight_init_values[layer_id].weight = ml_matrix_create(size);
		bias_data = (double *)bias_weight_init_values[layer_id].bias->data;
		weight_table
			= (double **)bias_weight_init_values[layer_id].weight->table;
		size.rows = -1;
		while (++size.rows < num_of_nodes[layer_id])
		{
			row = file_attr->row_array[row_id];
			size.cols = -1;
			read_and_validate(row[size.cols + 1], E_DOUBLE,
				&bias_data[size.rows]);
			while (++size.cols < num_of_nodes[layer_id - 1])
				read_and_validate(row[size.cols + 1], E_DOUBLE,
					&weight_table[size.rows][size.cols]);
			row_id++;
		}
		layer_id++;
	}
	return (bias_weight_init_values);
}

t_hyper_params	*hyper_params_init(
						const char *const weight_bias_file,
						const t_hyper_params *const input_hyper_params,
						const size_t num_of_input_functions,
						const size_t num_of_output_functions)
{
	t_hyper_params	*hyper_params;
	t_file_attr		*file_attr;

	hyper_params = ft_memalloc(sizeof(*hyper_params));
	if (input_hyper_params->weight_init_mode == E_TRAINED)
	{
		file_attr = ft_read_file(weight_bias_file, E_CSV);
		hyper_params->num_of_layers = get_number_of_layers(file_attr);
		hyper_params->num_of_nodes = get_number_of_nodes(file_attr,
				hyper_params->num_of_layers, num_of_input_functions,
				num_of_output_functions);
		hyper_params->bias_weight_init_values
			= get_bias_weight_init_values(file_attr,
				hyper_params->num_of_layers, hyper_params->num_of_nodes);
	}
	else
	{
		hyper_params->num_of_layers = NUM_OF_LAYERS;
		hyper_params->num_of_nodes
			= get_number_of_nodes_default(hyper_params->num_of_layers);
	}
	hyper_params->activation_types
		= get_activation_types(hyper_params->num_of_layers);
	hyper_params->dataset_split_order = input_hyper_params->dataset_split_order;
	hyper_params->epochs = input_hyper_params->epochs;
	hyper_params->learning_rate = input_hyper_params->learning_rate;
	hyper_params->weight_init_mode = input_hyper_params->weight_init_mode;
	return (hyper_params);
}
