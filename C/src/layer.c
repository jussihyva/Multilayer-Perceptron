/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:29:55 by juhani            #+#    #+#             */
/*   Updated: 2021/12/03 10:53:08 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	layer_input_print(const t_layer_input *const layer_input)
{
	ft_printf("LAYER: %d\n", layer_input->layer_type);
	ml_matrix_print(" (A) Output", layer_input->a_output);
	ft_printf("LAYER: %d\n", layer_input->layer_type);
	ml_matrix_print(" (X) Input", layer_input->x_input);
	ml_matrix_print(" (X) Output", layer_input->a_output);
	return ;
}

void	layer_input_calculation(const void *const layer)
{
	const t_layer_input	*layer_input;

	layer_input = (t_layer_input *)layer;
	normalize(layer_input->x_input, layer_input->a_output);
	if (ft_logging_level() <= LOG_DEBUG)
		layer_input_print(layer_input);
	return ;
}

void	layer_hidden_calculation(const void *const layer)
{
	const t_layer_hidden	*layer_hidden;

	layer_hidden = (t_layer_hidden *)layer;
	linear_function(layer);
	ml_sigmoid(layer_hidden->z, layer_hidden->a_output);
	return ;
}

void	layer_output_calculation(const void *const layer)
{
	const t_layer_output	*layer_output;

	layer_output = (t_layer_output *)layer;
	ml_matrix_cost(layer_output->y, layer_output->y_hat, layer_output->cost);
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
