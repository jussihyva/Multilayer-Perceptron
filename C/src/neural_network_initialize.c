/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neural_network_initialize.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:15:53 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/24 13:13:17 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static t_layer	*layer_init(
					const size_t num_of_nodes,
					const t_matrix *const input)
{
	t_layer		*layer;
	size_t		num_of_inputs;
	size_t		num_of_examples;

	layer = ft_memalloc(sizeof(*layer));
	layer->num_of_nodes = num_of_nodes;
	layer->a = input;
	num_of_inputs = input->size.rows;
	num_of_examples = input->size.cols;
	layer->z = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->y_hat = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->weight = ml_matrix_create(layer->num_of_nodes, num_of_inputs);
	layer->weight->column_names.lengths = input->row_names.lengths;
	layer->weight->column_names.names = input->row_names.names;
	layer->bias = ml_vector_create(layer->num_of_nodes);
	layer->derivative_b = ml_vector_create(layer->num_of_nodes);
	layer->derivative_w = ml_matrix_create(layer->num_of_nodes, num_of_inputs);
	layer->derivative_z = ml_matrix_create(layer->num_of_nodes,
			num_of_examples);
	return (layer);
}

t_neural_network	*neural_network_init(const t_dataset *const dataset)
{
	t_neural_network	*neural_network;
	size_t				i;
	const t_matrix		*input;

	neural_network = ft_memalloc(sizeof(*neural_network));
	neural_network->layers = ft_memalloc(sizeof(*neural_network->layers)
			* (NUM_OF_HIDDEN_LAYERS + 1));
	i = -1;
	while (++i <= NUM_OF_HIDDEN_LAYERS)
	{
		if (i)
			input = neural_network->layers[i - 1]->z;
		else
			input = dataset->x;
		neural_network->layers[i] = layer_init(g_layer_attrs[i].nodes,
				input);
	}
	return (neural_network);
}
