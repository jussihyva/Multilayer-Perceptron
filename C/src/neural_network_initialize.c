/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neural_network_initialize.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:15:53 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/13 19:20:31 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

t_neural_network	*neural_network_initialize(t_dataset *dataset)
{
	t_neural_network	*neural_network;
	size_t				num_of_examples;
	size_t				num_of_functions;
	t_layer				*layer;

	neural_network = ft_memalloc(sizeof(*neural_network));
	neural_network->layers = ft_memalloc(sizeof(*neural_network->layers)
			* NEURAL_NETWORK_NUM_OF_LAYERS);
	layer = &neural_network->layers[0];
	layer->num_of_nodes = 2;
	num_of_examples = dataset->x->size.cols;
	num_of_functions = dataset->x->size.rows;
	layer->a = dataset->x;
	layer->z = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->y_hat = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->weight = ml_matrix_create(layer->num_of_nodes, num_of_functions);
	layer->bias = ml_vector_create(num_of_functions);
	return (neural_network);
}
