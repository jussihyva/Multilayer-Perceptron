/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   propagation_backward.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:23:05 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/06 12:49:38 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	layer_hidden_print(const t_layer_hidden *const layer_hidden)
{
	const t_weight_bias		*weight_bias;
	const t_weight_bias		*d_weight_bias;

	weight_bias = &layer_hidden->weight_bias;
	d_weight_bias = &layer_hidden->d_weight_bias;
	ft_printf("LAYER: %lu\n", layer_hidden->id);
	ml_matrix_print(" (g') G_prime", layer_hidden->g_prime);
	ml_matrix_print(" (W[l + 1]) Weight transposed", layer_hidden->weight_transposed);
	ml_matrix_print(" (dZ) Derivative Z", layer_hidden->d_z);
	ml_matrix_print(" (dW) Derivative Weight", d_weight_bias->weight);
	ml_matrix_print(" (W) Weight", weight_bias->weight);
	ml_vector_print(" (B) Bias", weight_bias->bias);
	return ;
}

static void	weight_bias_update(
						const t_weight_bias *const weight_bias,
						const t_weight_bias *const d_weight_bias,
						const double learning_rate)
{
	size_t		i;
	size_t		total_size;

	total_size = weight_bias->weight->size.rows
		* weight_bias->weight->size.cols;
	i = -1;
	while (++i < total_size)
		((double *)weight_bias->weight->data)[i] -= learning_rate
			* ((double *)d_weight_bias->weight->data)[i];
	total_size = weight_bias->bias->size;
	i = -1;
	while (++i < total_size)
		((double *)weight_bias->bias->data)[i] -= learning_rate
			* ((double *)d_weight_bias->bias->data)[i];
	return ;
}

static void	propagation_backward_input(const t_layer_input *const layer)
{

	(void)layer;
	return ;
}

static void	propagation_backward_hidden(
								const void *const layer,
								const t_matrix *const activation_input,
								const t_matrix *const weight,
								const t_matrix *const d_z)
{
	t_layer_hidden		*layer_hidden;
	size_t				layer_id;
	size_t				example_id;
	size_t				node_id;
	size_t				function_id;

	layer_hidden = (t_layer_hidden *)layer;
	layer_id = layer_hidden->id;
	ml_matrix_reset(layer_hidden->d_z);
	g_prime_sigmoid(layer_hidden->a, layer_hidden->g_prime);
	ml_transpose(weight, layer_hidden->weight_transposed);
	example_id = -1;
	while (++example_id < d_z->size.cols)
	{
		node_id = -1;
		while (++node_id < g_layer_attrs[layer_id].nodes)
		{
			function_id = -1;
			while (++function_id < layer_hidden->weight_transposed->size.cols)
			{
				((double **)layer_hidden->d_z->table)[node_id][example_id]
					+= ((double **)layer_hidden->weight_transposed
					->table)[node_id][function_id]
					* ((double **)d_z->table)[function_id][example_id];
			}
			((double **)layer_hidden->d_z->table)[node_id][example_id]
				*= ((double **)layer_hidden->g_prime->table)[node_id]
				[example_id];
		}
	}
	derivative_w(activation_input, layer_hidden->d_z,
		layer_hidden->d_weight_bias.weight);
	derivative_b(layer_hidden->d_z, layer_hidden->d_weight_bias.bias);
	weight_bias_update(&layer_hidden->weight_bias, &layer_hidden->d_weight_bias,
		layer_hidden->hyper_params.learning_rate);
	if (ft_logging_level() <= LOG_DEBUG)
		layer_hidden_print(layer_hidden);
	return ;
}

static void	propagation_backward_output(
								const t_layer_output *const layer,
								const t_matrix *const activation_input)
{
	derivative_z_cost(layer->y_hat, layer->y, layer->d_z);
	derivative_w(activation_input, layer->d_z,
		layer->d_weight_bias.weight);
	derivative_b(layer->d_z, layer->d_weight_bias.bias);
	weight_bias_update(&layer->weight_bias, &layer->d_weight_bias,
		layer->hyper_params.learning_rate);
	return ;
}

// void	set_propagation_backward_functions(
// 		t_fn_propagation_backward *const fn_propagation_backward)
// {
// 	size_t		i;

// 	i = -1;
// 	while (++i < NUM_OF_LAYERS)
// 	{
// 		if (!i)
// 			fn_propagation_backward[i] = propagation_backward_input;
// 		else if (i == (NUM_OF_LAYERS - 1))
// 			fn_propagation_backward[i] = propagation_backward_output;
// 		else
// 			fn_propagation_backward[i] = propagation_backward_hidden;
// 	}
// 	return ;
// }

const t_matrix	*get_activation_input(
							const t_neural_network *const neural_network,
							const size_t layer_id)
{
	size_t				prev_layer_id;
	const t_matrix		*activation_input;

	activation_input = NULL;
	if (layer_id)
	{
		prev_layer_id = layer_id - 1;
		if (neural_network->layer_types[prev_layer_id] == E_LAYER_HIDDEN)
			activation_input
				= ((t_layer_hidden *)neural_network->layers[prev_layer_id])->a;
		else
			activation_input
				= ((t_layer_input *)neural_network->layers[prev_layer_id])->a;
	}
	return (activation_input);
}

static void	get_previous_weight_and_d_z(
								const size_t i,
								const t_neural_network *const neural_network,
								const t_matrix **const weight,
								const t_matrix **const d_z)
{
	size_t						next_layer_id;
	t_layer_type				next_layer_type;
	const void *const			*layers;
	const void					*next_layer;

	next_layer_id = i + 1;
	*weight = NULL;
	*d_z = NULL;
	if (next_layer_id != NUM_OF_LAYERS)
	{
		layers = neural_network->layers;
		next_layer_type = neural_network->layer_types[next_layer_id];
		next_layer = layers[next_layer_id];
		if (next_layer_type == E_LAYER_HIDDEN)
		{
			*weight = ((t_layer_hidden *)next_layer)->d_weight_bias.weight;
			*d_z = ((t_layer_hidden *)next_layer)->d_z;
		}
		else if (next_layer_type == E_LAYER_OUTPUT)
		{
			*weight = ((t_layer_output *)next_layer)->weight_bias.weight;
			*d_z = ((t_layer_output *)next_layer)->d_z;
		}
		else
			FT_LOG_FATAL("Unknown layer type (%d). "
				"Type should be either HIDDEN or OUTPUT.", next_layer_type);
	}
	return ;
}

void	propagation_backward(const t_neural_network *const neural_network)
{
	size_t				i;
	const t_matrix		*activation_input;
	const t_matrix		*weight;
	const t_matrix		*d_z;
	const void			**layers;

	layers = neural_network->layers;
	i = NUM_OF_LAYERS;
	while (--i)
	{
		activation_input = get_activation_input(neural_network, i);
		if (neural_network->layer_types[i] == E_LAYER_INPUT)
			propagation_backward_input(layers[i]);
		if (neural_network->layer_types[i] == E_LAYER_OUTPUT)
			propagation_backward_output(layers[i], activation_input);
		else
		{
			get_previous_weight_and_d_z(i, neural_network, &weight, &d_z);
			propagation_backward_hidden(layers[i], activation_input, weight, d_z);
		}
	}
	return ;
}
