/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neural_network_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:15:53 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/08 16:47:43 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static t_layer_input	*layer_input_init(
					const size_t id,
					const size_t num_of_examples,
					const t_matrix *const x,
					const t_hyper_params *const hyper_params)
{
	t_layer_input		*layer;
	size_t				num_of_nodes;

	num_of_nodes = g_layer_attrs[id].nodes;
	layer = ft_memalloc(sizeof(*layer));
	layer->id = id;
	layer->num_of_nodes = num_of_nodes;
	layer->x = x;
	layer->a = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->fn_normalize = normalize;
	layer->layer_type = g_layer_attrs[id].layer_type;
	layer->hyper_params = hyper_params;
	return (layer);
}

static void	weight_bias_init(
					const size_t id,
					t_weight_bias *const weight_bias,
					t_weight_bias *const d_weight_bias,
					const t_name_array *const row_names)
{
	size_t		num_of_activation_functions;
	size_t		num_of_nodes;

	num_of_nodes = g_layer_attrs[id].nodes;
	num_of_activation_functions = g_layer_attrs[id - 1].nodes;
	weight_bias->weight = ml_matrix_create(num_of_nodes,
			num_of_activation_functions);
	weight_bias->bias = ml_vector_create(num_of_nodes);
	d_weight_bias->bias = ml_vector_create(num_of_nodes);
	d_weight_bias->weight = ml_matrix_create(num_of_nodes,
			num_of_activation_functions);
	weight_bias->weight->column_names.lengths = row_names->lengths;
	weight_bias->weight->column_names.names = row_names->names;
	return ;
}

static t_layer_hidden	*layer_hidden_init(
								const size_t id,
								const size_t num_of_examples,
								const t_hyper_params *const hyper_params)
{
	t_layer_hidden		*layer;
	size_t				num_of_activation_functions;
	size_t				num_of_nodes;

	num_of_nodes = g_layer_attrs[id].nodes;
	layer = ft_memalloc(sizeof(*layer));
	layer->id = id;
	layer->num_of_nodes = num_of_nodes;
	num_of_activation_functions = g_layer_attrs[id - 1].nodes;
	layer->z = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->a = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->weight_transposed = ml_matrix_create(num_of_nodes,
			g_layer_attrs[id + 1].nodes);
	weight_bias_init(layer->id, &layer->weight_bias, &layer->d_weight_bias,
		&layer->a->row_names);
	layer->d_z = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->g_prime = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->layer_type = g_layer_attrs[id].layer_type;
	layer->hyper_params = hyper_params;
	return (layer);
}

static t_layer_output	*layer_output_init(
								const size_t id,
								const t_matrix *const y,
								const size_t num_of_examples,
								const t_hyper_params *const hyper_params)
{
	t_layer_output		*layer;
	size_t				num_of_activation_functions;
	size_t				num_of_nodes;

	num_of_nodes = g_layer_attrs[id].nodes;
	layer = ft_memalloc(sizeof(*layer));
	layer->id = id;
	layer->num_of_nodes = num_of_nodes;
	layer->y = y;
	num_of_activation_functions = g_layer_attrs[id - 1].nodes;
	layer->z = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->y_hat = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	weight_bias_init(layer->id, &layer->weight_bias, &layer->d_weight_bias,
		&layer->y->row_names);
	layer->d_z = ml_matrix_create(layer->num_of_nodes,
			num_of_examples);
	layer->cost = ml_vector_create(layer->num_of_nodes);
	layer->layer_type = g_layer_attrs[id].layer_type;
	layer->hyper_params = hyper_params;
	return (layer);
}

static t_layer_type	set_layer_type(const size_t layer_id)
{
	t_layer_type	layer_type;

	if (layer_id == 0)
		layer_type = E_LAYER_INPUT;
	else if (layer_id == (NUM_OF_LAYERS - 1))
		layer_type = E_LAYER_OUTPUT;
	else
		layer_type = E_LAYER_HIDDEN;
	return layer_type;
}

static const void	*layer_init(
						const size_t i,
						const t_layer_type layer_type,
						const t_dataset *const dataset,
						const t_hyper_params *const hyper_params)
{
	const void	*layer;
	size_t		num_of_examples;

	num_of_examples = dataset->y->size.cols;
	if (layer_type == E_LAYER_INPUT)
		layer = layer_input_init(i, num_of_examples, dataset->x, hyper_params);
	else if (i == (NUM_OF_LAYERS - 1))
		layer = layer_output_init(i, dataset->y, num_of_examples, hyper_params);
	else
		layer = layer_hidden_init(i, num_of_examples, hyper_params);
	return (layer);
}

t_neural_network	*neural_network_init(
								const t_dataset *const dataset,
								const t_hyper_params *const hyper_params)
{
	t_neural_network	*neural_network;
	size_t				i;

	neural_network = ft_memalloc(sizeof(*neural_network));
	neural_network->layers
		= ft_memalloc(sizeof(*neural_network->layers) * NUM_OF_LAYERS);
	neural_network->layer_types
		= ft_memalloc(sizeof(*neural_network->layer_types) * NUM_OF_LAYERS);
	i = -1;
	while (++i < NUM_OF_LAYERS)
	{
		neural_network->layer_types[i] = set_layer_type(i);
		neural_network->layers[i] = layer_init(i, neural_network
				->layer_types[i], dataset, hyper_params);
	}
	return (neural_network);
}

void	neural_network_remove(const t_neural_network **neural_network)
{
	layers_remove(&(*neural_network)->layers);
	ft_memdel((void **)&(*neural_network)->layer_types);
	ft_memdel((void **)neural_network);
	return ;
}
