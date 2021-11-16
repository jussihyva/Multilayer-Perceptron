/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:54:43 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/15 15:26:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	add_bias_value(
						const size_t example_id,
						const t_matrix *const z,
						const t_vector *const bias)
{
	size_t		node_id;

	node_id = -1;
	while (++node_id < z->size.rows)
	{
		((double **)z->table)[node_id][example_id]
			+= ((double *)bias->data)[node_id];
	}
	return ;
}

void	linear_function(const t_layer *const layer)
{
	size_t		function_id;
	size_t		example_id;
	size_t		node_id;
	double		**table_z;

	ml_matrix_reset(layer->z);
	ml_matrix_print("Weight", layer->weight);
	ml_vector_print("Bias", layer->bias);
	table_z = (double **)layer->z->table;
	example_id = -1;
	while (++example_id < layer->a->size.cols)
	{
		node_id = -1;
		while (++node_id < layer->z->size.rows)
		{
			function_id = -1;
			while (++function_id < layer->a->size.rows)
			{
				table_z[node_id][example_id]
					+= ((double **)layer->weight->table)[node_id][function_id]
					* ((double **)layer->a->table)[function_id][example_id];
			}
		}
		add_bias_value(example_id, layer->z, layer->bias);
	}
	ml_matrix_print("Z", layer->z);
	return ;
}