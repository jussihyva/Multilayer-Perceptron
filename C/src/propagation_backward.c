/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   propagation_backward.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:23:05 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/06 01:24:38 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	weight_bias_print(const t_weight_bias *const weight_bias)
{
	// ft_printf("LAYER: %d\n", layer->layer_type);
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
	t_layer_hidden		*layer_hidden;
	size_t				example_id;
	size_t				node_id;
	size_t				function_id;

	layer_hidden = (t_layer_hidden *)layer;
	ml_matrix_reset(layer_hidden->d_z);
	g_prime_sigmoid(layer_hidden->a_output, layer_hidden->g_prime);
	ml_transpose(weight, layer_hidden->weight_transposed);
	example_id = -1;
	while (++example_id < d_z->size.cols)
	{
		node_id = -1;
		while (++node_id < d_z->size.rows)
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
	derivative_w(layer_hidden->a_input, layer_hidden->d_z,
		layer_hidden->d_weight_bias.weight);
	derivative_b(layer_hidden->d_z, layer_hidden->d_weight_bias.bias);
	weight_bias_update(&layer_hidden->weight_bias, &layer_hidden->d_weight_bias,
		layer_hidden->hyper_params.learning_rate);
	if (ft_logging_level() <= LOG_DEBUG)
		weight_bias_print(&layer_hidden->weight_bias);
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
