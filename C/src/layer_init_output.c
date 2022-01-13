/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_init_output.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:01:10 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/13 11:35:29 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	part_1(
				t_layer_output *layer,
				t_dataset **dataset_array,
				const size_t *num_of_examples)
{
	t_size_2d			size;

	layer->y_train = dataset_array[E_TRAIN]->y;
	layer->y_test = dataset_array[E_TEST]->y;
	size.rows = layer->hyper_params->num_of_nodes[layer->id];
	size.cols = num_of_examples[E_TRAIN];
	layer->z_train = ml_matrix_create(size);
	layer->y_hat_train = ml_matrix_create(size);
	layer->d_z = ml_matrix_create(size);
	size.cols = num_of_examples[E_TEST];
	layer->z_test = ml_matrix_create(size);
	layer->y_hat_test = ml_matrix_create(size);
	return ;
}

static void	part_2(
			t_layer_output *layer,
			const size_t *num_of_examples)
{
	t_size_2d		size;

	size.rows = layer->hyper_params->num_of_nodes[layer->id];
	size.cols = layer->hyper_params->num_of_nodes[layer->id - 1];
	bias_weight_init(size, &layer->weight_bias, NULL,
		layer->hyper_params->weight_init_mode);
	bias_weight_init(size, &layer->d_weight_bias, NULL, E_ZERO);
	layer->cost[E_TRAIN] = ml_vector_create(size.rows);
	layer->cost[E_TEST] = ml_vector_create(size.rows);
	layer->layer_type = set_layer_type(layer->id,
			layer->hyper_params->num_of_layers);
	layer->num_of_nodes = layer->hyper_params->num_of_nodes[layer->id];
	layer->activation_type = layer->hyper_params->activation_types[layer->id];
	size.cols = num_of_examples[E_TRAIN];
	layer->softmax = ml_matrix_create(size);
	size.rows = num_of_examples[E_TRAIN];
	layer->argmax = ml_vector_create(size.rows);
	layer->argmax_values = ml_vector_create(size.rows);
	return ;
}

t_layer_output	*layer_init_output(
								const size_t id,
								t_dataset **dataset_array,
								const size_t *num_of_examples,
								const t_hyper_params *const hyper_params)
{
	t_layer_output		*layer;

	layer = ft_memalloc(sizeof(*layer));
	layer->hyper_params = hyper_params;
	layer->id = id;
	part_1(layer, dataset_array, num_of_examples);
	part_2(layer, num_of_examples);
	return (layer);
}
