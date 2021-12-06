/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:29:55 by juhani            #+#    #+#             */
/*   Updated: 2021/12/06 15:30:08 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	layer_input_print(const t_layer_input *const layer)
{
	ft_printf("LAYER: %lu\n", layer->id);
	ml_matrix_print(" X ", layer->x);
	ml_matrix_print(" A ", layer->a);
	return ;
}

static void	layer_output_print(const t_layer_output *const layer)
{
	ft_printf("LAYER: %lu\n", layer->id);
	ml_matrix_print(" (Y_hat) Prediction", layer->y_hat);
	ml_matrix_print(" (Y) Observation", layer->y);
	ml_vector_print(" Cost", layer->cost);
	return ;
}

void	propagation_forward_input(const t_layer_input *const layer)
{
	static t_bool	is_normalized = E_FALSE;

	if (!is_normalized)
	{
		normalize(layer->x, layer->a);
		is_normalized = E_TRUE;
		if (ft_logging_level() <= LOG_DEBUG)
			layer_input_print(layer);
	}
	return ;
}

void	propagation_forward_hidden(
						const t_layer_hidden *const layer,
						const t_matrix *const activation_input)
{
	linear_function_hidden(layer, activation_input);
	ml_sigmoid(layer->z, layer->a);
	return ;
}

void	propagation_forward_output(
						const t_layer_output *const layer,
						const t_matrix *const activation_input)
{
	linear_function_output(layer, activation_input);
	ml_sigmoid(layer->z, layer->y_hat);
	ml_matrix_cost(layer->y, layer->y_hat, layer->cost);
	if (ft_logging_level() <= LOG_DEBUG)
		layer_output_print(layer);
	return ;
}

void	layers_remove(void ***layers)
{
	const void			*layer;
	size_t				i;

	i = -1;
	while (++i < NUM_OF_LAYERS)
	{
		layer = (*layers)[i];
		// ml_matrix_remove((t_matrix **)&layer->weight);
		// ml_vector_remove((t_vector **)&layer->bias);
		// ml_matrix_remove((t_matrix **)&layer->z);
		// ml_matrix_remove((t_matrix **)&layer->a_output);
		// ml_vector_remove((t_vector **)&(*layer)->cost);
		// ml_matrix_remove((t_matrix **)&layer->d_weight);
		// ml_vector_remove((t_vector **)&layer->d_bias);
		// ml_matrix_remove((t_matrix **)&layer->d_z);
		ft_memdel((void **)&(*layers)[i]);
	}
	ft_memdel((void **)layers);
	return ;
}
