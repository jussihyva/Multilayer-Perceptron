/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   propagation_backward.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:23:05 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/03 16:40:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	layer_hidden_print(const t_layer_hidden *const layer)
{
	const t_weight_bias		*weight_bias;
	const t_weight_bias		*d_weight_bias;

	weight_bias = &layer->weight_bias;
	d_weight_bias = &layer->d_weight_bias;
	ft_printf("LAYER: %lu\n", layer->id);
	ml_matrix_print(" (g') G_prime", layer->g_prime);
	ml_matrix_print(" (W[l + 1]) Weight transposed", layer->weight_transposed);
	ml_matrix_print(" (dZ) Derivative Z", layer->d_z);
	ml_matrix_print(" (dW) Derivative Weight", d_weight_bias->weight);
	ml_matrix_print(" (W) Weight", weight_bias->weight);
	ml_vector_print(" (B) Bias", weight_bias->bias);
	return ;
}

static void	layer_output_print(const t_layer_output *const layer)
{
	const t_weight_bias		*weight_bias;
	const t_weight_bias		*d_weight_bias;

	weight_bias = &layer->weight_bias;
	d_weight_bias = &layer->d_weight_bias;
	ft_printf("LAYER: %lu\n", layer->id);
	ml_matrix_print(" (dZ) Derivative Z", layer->d_z);
	ml_matrix_print(" (dW) Derivative Weight", d_weight_bias->weight);
	ml_matrix_print(" (W) Weight", weight_bias->weight);
	ml_vector_print(" (B) Bias", weight_bias->bias);
	return ;
}

static void	weight_bias_update(const size_t layer_id,
						const t_weight_bias *const weight_bias,
						const t_weight_bias *const d_weight_bias,
						const t_hyper_params *const hyper_params)
{
	weight_update(layer_id, weight_bias->weight, d_weight_bias->weight,
		hyper_params);
	bias_update(layer_id, weight_bias->bias, d_weight_bias->bias, hyper_params);
	send_bias_values_to_database(layer_id, weight_bias->bias, hyper_params);
	send_weight_values_to_database(layer_id, weight_bias->weight, hyper_params);
	return ;
}

static void	propagation_backward_input(void)
{
	return ;
}

static void	propagation_backward_hidden(
								const t_layer_hidden *const layer,
								const t_matrix *const activation_input,
								const t_matrix *const weight,
								const t_matrix *const d_z)
{
	size_t				layer_id;
	size_t				example_id;
	size_t				node_id;
	size_t				function_id;

	layer_id = layer->id;
	ml_matrix_reset(layer->d_z);
	g_prime(layer->z, layer->a, layer->g_prime, layer->activation_type);
	ml_transpose(weight, layer->weight_transposed);
	example_id = -1;
	while (++example_id < d_z->size.cols)
	{
		node_id = -1;
		while (++node_id < layer->num_of_nodes)
		{
			function_id = -1;
			while (++function_id < layer->weight_transposed->size.cols)
			{
				((double **)layer->d_z->table)[node_id][example_id]
					+= ((double **)layer->weight_transposed
						->table)[node_id][function_id]
					* ((double **)d_z->table)[function_id][example_id];
			}
			((double **)layer->d_z->table)[node_id][example_id]
				*= ((double **)layer->g_prime->table)[node_id][example_id];
		}
	}
	derivative_w(activation_input, layer->d_z, layer->d_weight_bias.weight);
	derivative_b(layer->d_z, layer->d_weight_bias.bias);
	weight_bias_update(layer_id, &layer->weight_bias, &layer->d_weight_bias,
		layer->hyper_params);
	if (ft_logging_level() <= LOG_DEBUG)
		layer_hidden_print(layer);
	return ;
}

static void	propagation_backward_output(
								const t_layer_output *const layer,
								const t_matrix *const activation_input)
{
	size_t			layer_id;

	layer_id = layer->id;
	derivative_z_cost(layer->y_hat, layer->y, layer->d_z);
	derivative_w(activation_input, layer->d_z,
		layer->d_weight_bias.weight);
	derivative_b(layer->d_z, layer->d_weight_bias.bias);
	weight_bias_update(layer_id, &layer->weight_bias, &layer->d_weight_bias,
		layer->hyper_params);
	if (ft_logging_level() <= LOG_DEBUG)
		layer_output_print(layer);
	return ;
}

const t_matrix	*get_activation_input(
							void *const *const layers,
							const t_layer_type *const layer_types,
							const size_t layer_id)
{
	size_t				prev_layer_id;
	const t_matrix		*activation_input;

	activation_input = NULL;
	if (layer_id)
	{
		prev_layer_id = layer_id - 1;
		if (layer_types[prev_layer_id] == E_LAYER_HIDDEN)
			activation_input = ((t_layer_hidden *)layers[prev_layer_id])->a;
		else
			activation_input = ((t_layer_input *)layers[prev_layer_id])->a;
	}
	return (activation_input);
}

static void	get_previous_weight_and_d_z(
								void *const next_layer,
								const t_layer_type layer_type,
								const t_matrix **const weight,
								const t_matrix **const d_z)
{
	t_layer_type				next_layer_type;

	next_layer_type = layer_type;
	if (next_layer_type == E_LAYER_HIDDEN)
	{
		*weight = ((t_layer_hidden *)next_layer)->weight_bias.weight;
		*d_z = ((t_layer_hidden *)next_layer)->d_z;
	}
	else if (next_layer_type == E_LAYER_OUTPUT)
	{
		*weight = ((t_layer_output *)next_layer)->weight_bias.weight;
		*d_z = ((t_layer_output *)next_layer)->d_z;
	}
	else
	{
		*weight = NULL;
		*d_z = NULL;
		FT_LOG_FATAL("Unknown layer type (%d). "
			"Type should be either HIDDEN or OUTPUT.", next_layer_type);
	}
	return ;
}

void	propagation_backward(
					void *const *const layers,
					const t_layer_type *const layer_types,
					const size_t num_of_layers)
{
	size_t				i;
	const t_matrix		*activation_input;
	const t_matrix		*weight;
	const t_matrix		*d_z;

	i = num_of_layers;
	while (i--)
	{
		activation_input = get_activation_input(layers, layer_types, i);
		if (layer_types[i] == E_LAYER_INPUT)
			propagation_backward_input();
		else if (layer_types[i] == E_LAYER_OUTPUT)
			propagation_backward_output(layers[i], activation_input);
		else if (layer_types[i] == E_LAYER_HIDDEN)
		{
			get_previous_weight_and_d_z(layers[i + 1], layer_types[i + 1],
				&weight, &d_z);
			propagation_backward_hidden(layers[i], activation_input, weight,
				d_z);
		}
	}
	return ;
}
