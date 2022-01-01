/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 09:59:19 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/01 22:48:08 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static t_layer_type	set_layer_type(const size_t id, const size_t num_of_layers)
{
	t_layer_type	layer_type;

	if (id == 0)
		layer_type = E_LAYER_INPUT;
	else if (id == num_of_layers - 1)
		layer_type = E_LAYER_OUTPUT;
	else
		layer_type = E_LAYER_HIDDEN;
	return (layer_type);
}

static t_layer_input	*layer_init_input(
					const size_t id,
					const t_dataset *const *const dataset_array,
					const t_hyper_params *const hyper_params)
{
	t_layer_input		*layer;
	size_t				num_of_examples;

	layer = ft_memalloc(sizeof(*layer));
	layer->id = id;
	layer->num_of_nodes = hyper_params->num_of_nodes[id];
	layer->x_train = dataset_array[E_TRAIN]->x;
	layer->x_test = dataset_array[E_TEST]->x;
	num_of_examples = dataset_array[E_TRAIN]->x->size.cols;
	layer->a_train = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	num_of_examples = dataset_array[E_TEST]->x->size.cols;
	layer->a_test = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->fn_normalize = normalize;
	layer->layer_type = set_layer_type(id, hyper_params->num_of_layers);
	layer->hyper_params = hyper_params;
	return (layer);
}

static t_layer_hidden	*layer_init_hidden(
								const size_t id,
								const size_t *num_of_examples,
								const t_hyper_params *const hyper_params)
{
	t_layer_hidden		*layer;
	size_t				num_of_nodes;

	num_of_nodes = hyper_params->num_of_nodes[id];
	layer = ft_memalloc(sizeof(*layer));
	layer->id = id;
	layer->z_train = ml_matrix_create(num_of_nodes, num_of_examples[E_TRAIN]);
	layer->z_test = ml_matrix_create(num_of_nodes, num_of_examples[E_TEST]);
	layer->a_train = ml_matrix_create(num_of_nodes, num_of_examples[E_TRAIN]);
	layer->a_test = ml_matrix_create(num_of_nodes, num_of_examples[E_TEST]);
	layer->weight_transposed = ml_matrix_create(num_of_nodes,
			hyper_params->num_of_nodes[id + 1]);
	bias_weight_init(layer->id, &layer->weight_bias, NULL,
		hyper_params->weight_init_mode);
	bias_weight_init(layer->id, &layer->d_weight_bias, NULL, E_ZERO);
	layer->d_z = ml_matrix_create(num_of_nodes, num_of_examples[E_TRAIN]);
	layer->g_prime = ml_matrix_create(num_of_nodes, num_of_examples[E_TRAIN]);
	layer->layer_type = set_layer_type(id, hyper_params->num_of_layers);
	layer->hyper_params = hyper_params;
	layer->num_of_nodes = num_of_nodes;
	return (layer);
}

static t_layer_output	*layer_init_output(
								const size_t id,
								const t_dataset *const *const dataset_array,
								const size_t *num_of_examples,
								const t_hyper_params *const hyper_params)
{
	t_layer_output		*layer;
	size_t				num_of_nodes;

	num_of_nodes = hyper_params->num_of_nodes[id];
	layer = ft_memalloc(sizeof(*layer));
	layer->id = id;
	layer->y_train = dataset_array[E_TRAIN]->y;
	layer->y_test = dataset_array[E_TEST]->y;
	layer->z_train = ml_matrix_create(num_of_nodes, num_of_examples[E_TRAIN]);
	layer->z_test = ml_matrix_create(num_of_nodes, num_of_examples[E_TEST]);
	layer->y_hat_train = ml_matrix_create(num_of_nodes,
			num_of_examples[E_TRAIN]);
	layer->y_hat_test = ml_matrix_create(num_of_nodes, num_of_examples[E_TEST]);
	bias_weight_init(layer->id, &layer->weight_bias, NULL,
		hyper_params->weight_init_mode);
	bias_weight_init(layer->id, &layer->d_weight_bias, NULL, E_ZERO);
	layer->d_z = ml_matrix_create(num_of_nodes, num_of_examples[E_TRAIN]);
	layer->cost[E_TRAIN] = ml_vector_create(num_of_nodes);
	layer->cost[E_TEST] = ml_vector_create(num_of_nodes);
	layer->layer_type = set_layer_type(id, hyper_params->num_of_layers);
	layer->hyper_params = hyper_params;
	layer->num_of_nodes = num_of_nodes;
	return (layer);
}

void	*layer_init(
					const size_t i,
					const t_layer_type layer_type,
					const t_dataset *const *const dataset_array,
					const t_hyper_params *const hyper_params)
{
	void	*layer;
	size_t	num_of_examples[2];

	num_of_examples[E_TRAIN] = dataset_array[E_TRAIN]->x->size.cols;
	num_of_examples[E_TEST] = dataset_array[E_TEST]->x->size.cols;
	if (layer_type == E_LAYER_INPUT)
		layer = layer_init_input(i, dataset_array, hyper_params);
	else if (layer_type == E_LAYER_HIDDEN)
		layer = layer_init_hidden(i, num_of_examples, hyper_params);
	else if (layer_type == E_LAYER_OUTPUT)
		layer = layer_init_output(i, dataset_array, num_of_examples,
				hyper_params);
	else
	{
		layer = NULL;
		FT_LOG_FATAL("Layer type %d is unknown. ", layer_type);
	}
	return (layer);
}
