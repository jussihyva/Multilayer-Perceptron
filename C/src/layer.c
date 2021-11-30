/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhani <juhani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:29:55 by juhani            #+#    #+#             */
/*   Updated: 2021/11/30 23:20:09 by juhani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	layer_input_calculation(const void *const layer)
{
	const t_layer_input	*layer_input;

	layer_input = (t_layer_input *)layer;
	normalize(layer_input->x_input, layer_input->x_output);
	if (ft_logging_level() <= LOG_DEBUG)
	{
		ft_printf("LAYER: %lu\n", layer_input->id);
		ml_matrix_print(" (A) Output", layer_input->x_output);
	}
	if (ft_logging_level() <= LOG_DEBUG)
	{
		ft_printf("LAYER: %lu\n", layer_input->id);
		ml_matrix_print(" (X) Input", layer_input->x_input);
		ml_matrix_print(" (X) Output", layer_input->x_output);
	}
	return ;
}

// void	layer_calculation(
// 					const void *const layer,
// 					const t_layer_type layer_type)
// {
// 	if (layer_type == E_LAYER_INPUT)
// 		normalize(layer>x_input, layer_input->x_output);
// 	// linear_function(layer);
// 	// ml_sigmoid(layer->z, layer->a_output);
// 	return ;
// }
