/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   propagation_backward.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:23:05 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/07 11:12:30 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

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

static void	propagation_backward_hidden(
								const t_layer_hidden *const layer,
								const t_matrix *const activation_input,
								const t_matrix *const weight,
								const t_matrix *const d_z)
{
	size_t				layer_id;

	layer_id = layer->id;
	ml_matrix_reset(layer->d_z);
	g_prime(layer->z, layer->a, layer->g_prime, layer->activation_type);
	ml_transpose(weight, layer->weight_transposed);
	derivative_z(d_z, layer);
	derivative_w(activation_input, layer->d_z, layer->d_weight_bias.weight);
	derivative_b(layer->d_z, layer->d_weight_bias.bias);
	weight_bias_update(layer_id, &layer->weight_bias, &layer->d_weight_bias,
		layer->hyper_params);
	if (ft_logging_level() <= LOG_DEBUG)
		layer_print_hidden_b(layer);
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
		layer_print_output_b(layer);
	return ;
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
	size_t				layer_id_prev;

	i = num_of_layers;
	while (--i)
	{
		layer_id_prev = i - 1;
		activation_input = get_activation_input(layers[layer_id_prev],
				layer_types[layer_id_prev]);
		if (layer_types[i] == E_LAYER_OUTPUT)
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
