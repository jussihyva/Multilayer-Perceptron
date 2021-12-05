/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neural_network_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:15:53 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/06 00:46:43 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

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
	layer->id = id;
	layer->num_of_nodes = num_of_nodes;
	layer->x_input = input;
	layer->a_output = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->fn_normalize = normalize;
	layer->layer_type = E_LAYER_INPUT;
	layer->hyper_params.learning_rate = g_layer_attrs[id].learning_rate;
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
								const t_matrix *const a_input)
{
	t_layer_hidden		*layer;
	size_t				num_of_activation_functions;
	size_t				num_of_examples;
	size_t				num_of_nodes;

	num_of_examples = a_input->size.cols;
	num_of_nodes = g_layer_attrs[id].nodes;
	layer = ft_memalloc(sizeof(*layer));
	layer->id = id;
	layer->num_of_nodes = num_of_nodes;
	layer->a_input = a_input;
	num_of_activation_functions = layer->a_input->size.rows;
	layer->z = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->a_output = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->weight_transposed = ml_matrix_create(num_of_nodes,
			g_layer_attrs[id + 1].nodes);
	weight_bias_init(layer->id, &layer->weight_bias, &layer->d_weight_bias,
		&layer->a_input->row_names);
	layer->d_z = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->g_prime = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->layer_type = E_LAYER_HIDDEN;
	layer->hyper_params.learning_rate = g_layer_attrs[id].learning_rate;
	return (layer);
}

static t_layer_output	*layer_output_init(
								const size_t id,
								const t_matrix *const a_input,
								const t_matrix *const y)
{
	t_layer_output		*layer;
	size_t				num_of_activation_functions;
	size_t				num_of_examples;
	size_t				num_of_nodes;

	num_of_examples = a_input->size.cols;
	num_of_nodes = g_layer_attrs[id].nodes;
	layer = ft_memalloc(sizeof(*layer));
	layer->id = id;
	layer->num_of_nodes = num_of_nodes;
	layer->a_input = a_input;
	layer->y = y;
	num_of_activation_functions = layer->a_input->size.rows;
	layer->z = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	layer->y_hat = ml_matrix_create(layer->num_of_nodes, num_of_examples);
	weight_bias_init(layer->id, &layer->weight_bias, &layer->d_weight_bias,
		&layer->a_input->row_names);
	layer->d_z = ml_matrix_create(layer->num_of_nodes,
			num_of_examples);
	layer->cost = ml_vector_create(layer->num_of_nodes);
	layer->layer_type = E_LAYER_OUTPUT;
	layer->hyper_params.learning_rate = g_layer_attrs[id].learning_rate;
	return (layer);
}

static void	set_propagation_functions(
			t_fn_propagation_forward *const fn_propagation_forward)
{
	size_t		i;

	i = -1;
	while (++i < NUM_OF_LAYERS)
	{
		if (!i)
			fn_propagation_forward[i] = layer_input_calculation;
		else if (i == (NUM_OF_LAYERS - 1))
			fn_propagation_forward[i] = layer_output_calculation;
		else
			fn_propagation_forward[i] = layer_hidden_calculation;
	}
	return ;
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

static const t_matrix	*get_activation_input(
									const size_t i,
									const t_dataset *const dataset,
									const void *const *const layers,
									const t_layer_type *const layer_types)
{
	const t_matrix		*a_input;
	size_t				prev_layer_id;
	t_layer_type		prev_layer_type;
	const void			*prev_layer;

	if (layer_types[i] == E_LAYER_INPUT)
		a_input = dataset->x;
	else
	{
		prev_layer_id = i - 1;
		prev_layer_type = layer_types[prev_layer_id];
		prev_layer = layers[prev_layer_id];
		if (prev_layer_type == E_LAYER_INPUT)
			a_input = ((t_layer_input *)prev_layer)->a_output;
		else if (prev_layer_type == E_LAYER_HIDDEN)
			a_input = ((t_layer_hidden *)prev_layer)->a_output;
		else
		{
			a_input = NULL;
			FT_LOG_FATAL("Unknown layer type (%d). "
				"Type should be either INPUT or HIDDEN.", prev_layer_type);
		}
	}
	return (a_input);
}

static const void	*layer_init(
						const size_t i,
						const t_layer_type layer_type,
						const t_matrix *const a_input,
						const t_dataset *const dataset)
{
	const void	*layer;

	if (layer_type == E_LAYER_INPUT)
		layer = layer_input_init(i, a_input);
	else if (i == (NUM_OF_LAYERS - 1))
		layer = layer_output_init(i, a_input, dataset->y);
	else
		layer = layer_hidden_init(i, a_input);
	return (layer);
}

t_neural_network	*neural_network_init(const t_dataset *const dataset)
{
	t_neural_network	*neural_network;
	size_t				i;
	const t_matrix		*a_input;
	const void			**layers;
	t_layer_type		*layer_types;

	neural_network = ft_memalloc(sizeof(*neural_network));
	layers = neural_network->layers;
	layer_types = neural_network->layer_types;
	set_propagation_functions(neural_network->fn_propagation_forward);
	set_propagation_backward_functions(neural_network->fn_propagation_backward);
	i = -1;
	while (++i < NUM_OF_LAYERS)
	{
		layer_types[i] = set_layer_type(i);
		a_input = get_activation_input(i, dataset, layers, layer_types);
		layers[i] = layer_init(i, layer_types[i], a_input, dataset);
	}
	return (neural_network);
}
