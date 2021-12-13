/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 09:59:19 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/13 10:24:15 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static t_layer_input	*layer_init_input(
					const size_t id,
					const size_t num_of_examples,
					const t_matrix *const x,
					const t_hyper_params *const hyper_params)
{
	t_layer_input		*layer;
	size_t				num_of_nodes;

	num_of_nodes = g_layer_attrs[NUM_OF_LAYERS][id].nodes;
	layer = ft_memalloc(sizeof(*layer));
	layer->id = id;
	layer->num_of_nodes = num_of_nodes;
	layer->x = x;
	layer->a = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->fn_normalize = normalize;
	layer->layer_type = g_layer_attrs[NUM_OF_LAYERS][id].layer_type;
	layer->hyper_params = hyper_params;
	return (layer);
}

static t_layer_hidden	*layer_init_hidden(
								const size_t id,
								const size_t num_of_examples,
								const t_hyper_params *const hyper_params)
{
	t_layer_hidden		*layer;
	size_t				num_of_activation_functions;
	size_t				num_of_nodes;

	num_of_nodes = g_layer_attrs[NUM_OF_LAYERS][id].nodes;
	layer = ft_memalloc(sizeof(*layer));
	layer->id = id;
	layer->num_of_nodes = num_of_nodes;
	num_of_activation_functions = g_layer_attrs[NUM_OF_LAYERS][id - 1].nodes;
	layer->z = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->a = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->weight_transposed = ml_matrix_create(num_of_nodes,
			g_layer_attrs[NUM_OF_LAYERS][id + 1].nodes);
	bias_weight_init(layer->id, &layer->weight_bias, &layer->a->row_names);
	bias_weight_init(layer->id, &layer->d_weight_bias, NULL);
	layer->d_z = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->g_prime = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->layer_type = g_layer_attrs[NUM_OF_LAYERS][id].layer_type;
	layer->hyper_params = hyper_params;
	return (layer);
}

static t_layer_output	*layer_init_output(
								const size_t id,
								const t_matrix *const y,
								const size_t num_of_examples,
								const t_hyper_params *const hyper_params)
{
	t_layer_output		*layer;
	size_t				num_of_activation_functions;
	size_t				num_of_nodes;

	num_of_nodes = g_layer_attrs[NUM_OF_LAYERS][id].nodes;
	layer = ft_memalloc(sizeof(*layer));
	layer->id = id;
	layer->num_of_nodes = num_of_nodes;
	layer->y = y;
	num_of_activation_functions = g_layer_attrs[NUM_OF_LAYERS][id - 1].nodes;
	layer->z = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->y_hat = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	bias_weight_init(layer->id, &layer->weight_bias, NULL);
	bias_weight_init(layer->id, &layer->d_weight_bias, NULL);
	layer->d_z = ml_matrix_create(layer->num_of_nodes,
			num_of_examples);
	layer->cost = ml_vector_create(layer->num_of_nodes);
	layer->layer_type = g_layer_attrs[NUM_OF_LAYERS][id].layer_type;
	layer->hyper_params = hyper_params;
	return (layer);
}

const void	*layer_init(
					const size_t i,
					const t_layer_type layer_type,
					const t_dataset *const dataset,
					const t_hyper_params *const hyper_params)
{
	const void	*layer;
	size_t		num_of_examples;

	num_of_examples = dataset->y->size.cols;
	if (layer_type == E_LAYER_INPUT)
		layer = layer_init_input(i, num_of_examples, dataset->x, hyper_params);
	else if (layer_type == E_LAYER_HIDDEN)
		layer = layer_init_hidden(i, num_of_examples, hyper_params);
	else if (layer_type == E_LAYER_OUTPUT)
		layer = layer_init_output(i, dataset->y, num_of_examples, hyper_params);
	else
	{
		layer = NULL;
		FT_LOG_FATAL("Layer type %d is unknown. ", layer_type);
	}
	return (layer);
}
