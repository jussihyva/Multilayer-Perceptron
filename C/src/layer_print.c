/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:08:16 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/07 10:44:39 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	layer_print_input(const t_layer_input *const layer)
{
	ft_printf("LAYER: %lu\n", layer->id);
	ml_matrix_print(" X ", layer->x);
	ml_matrix_print(" A ", layer->a);
	return ;
}

void	layer_print_hidden_f(const t_layer_hidden *const layer)
{
	ft_printf("LAYER: %lu\n", layer->id);
	ml_matrix_print(" (z) Linear output", layer->z);
	ml_matrix_print(" (a) Activation output", layer->a);
	return ;
}

void	layer_print_hidden_b(const t_layer_hidden *const layer)
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

void	layer_print_output_f(const t_layer_output *const layer)
{
	ft_printf("LAYER: %lu\n", layer->id);
	ml_matrix_print(" (Y_hat) Prediction", layer->y_hat);
	ml_matrix_print(" (Y) Observation", layer->y);
	ml_vector_print(" Cost (TRAIN)", layer->cost[E_TRAIN]);
	ml_vector_print(" Cost (TEST)", layer->cost[E_TEST]);
	return ;
}

void	layer_print_output_b(const t_layer_output *const layer)
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
