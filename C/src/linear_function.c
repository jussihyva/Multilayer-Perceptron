/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:54:43 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/04 10:56:48 by jkauppi          ###   ########.fr       */
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

static void	linear_function(
					const t_matrix *const a_input,
					const t_matrix *const weight,
					const t_vector *const bias,
					t_matrix *const z)
{
	size_t		function_id;
	size_t		example_id;
	size_t		node_id;
	double		**table_z;

	ml_matrix_reset(z);
	table_z = (double **)z->table;
	example_id = -1;
	while (++example_id < a_input->size.cols)
	{
		node_id = -1;
		while (++node_id < z->size.rows)
		{
			function_id = -1;
			while (++function_id < a_input->size.rows)
			{
				table_z[node_id][example_id]
					+= ((double **)weight->table)[node_id][function_id]
					* ((double **)a_input
						->table)[function_id][example_id];
			}
		}
		add_bias_value(example_id, z, bias);
	}
	return ;
}

void	linear_function_hidden(const t_layer_hidden *const layer)
{
	linear_function(layer->a_input, layer->weight, layer->bias, layer->z);
}

void	linear_function_output(const t_layer_output *const layer)
{
	linear_function(layer->a_input, layer->weight, layer->bias, layer->z);
}
