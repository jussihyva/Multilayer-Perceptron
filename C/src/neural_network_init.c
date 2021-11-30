/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neural_network_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhani <juhani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:15:53 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/30 23:17:07 by juhani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static const t_layer_profile	g_layer_attrs[NUM_OF_LAYERS]
	= {{NUMBER_OF_COLUMNS}, {3}, {3}, {2}};
		// = {{2}};

static t_layer_input	*layer_input_init(
					const size_t id,
					const t_matrix *const input)
{
	t_layer_input		*layer;
	size_t				num_of_functions;
	size_t				num_of_examples;
	size_t				num_of_nodes;

	num_of_functions = input->size.rows;
	num_of_examples = input->size.cols;
	num_of_nodes = g_layer_attrs[id].nodes;
	layer = ft_memalloc(sizeof(*layer));
	layer->num_of_nodes = num_of_nodes;
	layer->x_input = input;
	layer->x_output = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->fn_normalize = normalize;
	layer->id = id;
	return (layer);
}

// static t_layer_hidden	*layer_init(
// 					const size_t num_of_nodes,
// 					const t_matrix *const input)
// {
// 	t_layer_hidden		*layer;
// 	size_t				num_of_inputs;
// 	size_t				num_of_examples;

// 	layer = ft_memalloc(sizeof(*layer));
// 	layer->num_of_nodes = num_of_nodes;
// 	layer->a_input = input;
// 	num_of_inputs = input->size.rows;
// 	num_of_examples = input->size.cols;
// 	layer->z = ml_matrix_create(layer->num_of_nodes, num_of_examples);
// 	layer->a_output = ml_matrix_create(layer->num_of_nodes, num_of_examples);
// 	layer->weight = ml_matrix_create(layer->num_of_nodes, num_of_inputs);
// 	layer->weight->column_names.lengths = input->row_names.lengths;
// 	layer->weight->column_names.names = input->row_names.names;
// 	layer->bias = ml_vector_create(layer->num_of_nodes);
// 	layer->d_bias = ml_vector_create(layer->num_of_nodes);
// 	layer->d_weight = ml_matrix_create(layer->num_of_nodes, num_of_inputs);
// 	layer->d_z = ml_matrix_create(layer->num_of_nodes,
// 			num_of_examples);
// 	return (layer);
// }

t_neural_network	*neural_network_init(const t_dataset *const dataset)
{
	t_neural_network	*neural_network;
	size_t				i;
	const t_matrix		*input;

	neural_network = ft_memalloc(sizeof(*neural_network));
	neural_network->layers = ft_memalloc(sizeof(*neural_network->layers)
			* (NUM_OF_LAYERS));
	i = -1;
	while (++i < NUM_OF_LAYERS)
	{
		if (i)
			;
			// input = neural_network->layers[i - 1]->z;
		else
		{
			input = dataset->x;
			neural_network->layers[i] = layer_input_init(i, input);
			neural_network->fn_layer_forward_propagation[i]
				= layer_input_calculation;
		}
	}
	return (neural_network);
}
