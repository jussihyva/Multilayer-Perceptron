/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bias_weight_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 10:17:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/15 14:36:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	bias_weight_init(
				const size_t id,
				t_weight_bias *const weight_bias,
				t_name *const row_name_array)
{
	size_t		num_of_activation_functions;
	size_t		num_of_nodes;

	num_of_nodes = g_layer_attrs[NUM_OF_LAYERS][id].nodes;
	num_of_activation_functions = g_layer_attrs[NUM_OF_LAYERS][id - 1].nodes;
	weight_bias->weight = ml_matrix_create(num_of_nodes,
			num_of_activation_functions);
	weight_bias->bias = ml_vector_create(num_of_nodes);
	if (row_name_array)
		weight_bias->weight->col_name_array = row_name_array;
	return ;
}
