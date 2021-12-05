/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   propagation_backward.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:23:05 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/05 14:34:40 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

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

static void	propagation_backward_input(
								const void *const layer,
								const t_matrix *const weight,
								const t_matrix *const d_z)
{
	t_layer_input	*layer_input;

	layer_input = (t_layer_input *)layer;
	(void)weight;
	(void)d_z;
	return ;
}

static void	propagation_backward_hidden(
								const void *const layer,
								const t_matrix *const weight,
								const t_matrix *const d_z)
{
	t_layer_hidden	*layer_input;

	layer_input = (t_layer_hidden *)layer;
	// layer_input->z * (1 - layer_input->z);
	(void)layer_input->d_z;
	(void)weight;
	(void)d_z;
	return ;
}

static void	propagation_backward_output(
								const void *const layer,
								const t_matrix *const weight,
								const t_matrix *const d_z)
{
	t_layer_output	*layer_output;

	(void)weight;
	(void)d_z;
	layer_output = (t_layer_output *)layer;
	derivative_z_cost(layer_output->y_hat, layer_output->y, layer_output->d_z);
	derivative_w(layer_output->a_input, layer_output->d_z,
		layer_output->d_weight_bias.weight);
	derivative_b(layer_output->d_z, layer_output->d_weight_bias.bias);
	weight_bias_update(&layer_output->weight_bias, &layer_output->d_weight_bias,
		layer_output->hyper_params.learning_rate);
	return ;
}

void	set_propagation_backward_functions(
		t_fn_propagation_backward *const fn_propagation_backward)
{
	size_t		i;

	i = -1;
	while (++i < NUM_OF_LAYERS)
	{
		if (!i)
			fn_propagation_backward[i] = propagation_backward_input;
		else if (i == (NUM_OF_LAYERS - 1))
			fn_propagation_backward[i] = propagation_backward_output;
		else
			fn_propagation_backward[i] = propagation_backward_hidden;
	}
	return ;
}
