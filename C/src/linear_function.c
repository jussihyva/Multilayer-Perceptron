/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:54:43 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/13 19:41:27 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	add_bias_value(
						const size_t example_id,
						const t_matrix *const z,
						const t_vector *const bias)
{
	size_t		function_id;

	function_id = -1;
	while (++function_id < z->size.rows)
	{
		((double **)z->table)[function_id][example_id]
			+= ((double *)bias->data)[function_id];
	}
	return ;
}

void	linear_function(const t_layer *const layer)
{
	size_t		x_row;
	size_t		example_id;
	size_t		z_row;

	ml_matrix_print("Weight", layer->weight);
	ml_vector_print("Bias", layer->bias);
	example_id = -1;
	while (++example_id < layer->a->size.cols)
	{
		z_row = -1;
		while (++z_row < layer->z->size.rows)
		{
			x_row = -1;
			while (++x_row < layer->a->size.rows)
			{
				((double **)layer->z->table)[z_row][example_id]
					+= ((double **)layer->weight->table)[z_row][x_row]
					* ((double **)layer->a->table)[x_row][example_id];
			}
		}
		add_bias_value(example_id, layer->z, layer->bias);
	}
	return ;
}
