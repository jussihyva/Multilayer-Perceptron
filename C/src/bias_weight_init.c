/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bias_weight_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 10:17:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/13 10:23:19 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	bias_weight_init(
				const size_t id,
				t_weight_bias *const weight_bias,
				const t_name_array *const row_names)
{
	size_t		num_of_activation_functions;
	size_t		num_of_nodes;

	num_of_nodes = g_layer_attrs[NUM_OF_LAYERS][id].nodes;
	num_of_activation_functions = g_layer_attrs[NUM_OF_LAYERS][id - 1].nodes;
	weight_bias->weight = ml_matrix_create(num_of_nodes,
			num_of_activation_functions);
	weight_bias->bias = ml_vector_create(num_of_nodes);
	if (row_names)
	{
		weight_bias->weight->column_names.lengths = row_names->lengths;
		weight_bias->weight->column_names.names = row_names->names;
	}
	return ;
}

