/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   propagation_forward.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:04:22 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/02 21:41:04 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	propagation_forward_input(t_layer_input *const layer)
{
	static t_bool	is_normalized[2] = {E_FALSE, E_FALSE};

	if (!is_normalized[layer->dataset_type])
	{
		normalize(layer->x, layer->a);
		is_normalized[layer->dataset_type] = E_TRUE;
		if (ft_logging_level() <= LOG_DEBUG)
			layer_print_input(layer);
	}
	return ;
}

static void	propagation_forward_hidden(
						t_layer_hidden *const layer,
						const t_matrix *const activation_input)
{
	linear_function_hidden(layer, activation_input);
	ml_sigmoid(layer->z, layer->a);
	return ;
}

static void	propagation_forward_output(
						t_layer_output *const layer,
						const t_matrix *const activation_input)
{
	linear_function_output(layer, activation_input);
	ml_sigmoid(layer->z, layer->y_hat);
	ml_matrix_cost(layer->y, layer->y_hat, layer->cost[layer->dataset_type]);
	if (ft_logging_level() <= LOG_DEBUG)
		layer_print_output(layer);
	return ;
}

void	propagation_forward(
					void *const *const layers,
					const t_layer_type *const layer_types,
					const size_t num_of_layers)
{
	size_t				i;
	const t_matrix		*activation_input;

	i = -1;
	while (++i < num_of_layers)
	{
		activation_input = get_activation_input(layers, layer_types, i);
		if (layer_types[i] == E_LAYER_INPUT)
			propagation_forward_input(layers[i]);
		else if (layer_types[i] == E_LAYER_OUTPUT)
			propagation_forward_output(layers[i], activation_input);
		else
			propagation_forward_hidden(layers[i], activation_input);
	}
	return ;
}
