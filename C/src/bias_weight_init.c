/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bias_weight_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 10:17:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/17 16:28:35 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	set_start_values(t_matrix *const weight)
{
	t_size_2d		i;
	double			rand_value;

	i.rows = -1;
	while (++i.rows < weight->size.rows)
	{
		i.cols = -1;
		while (++i.cols < weight->size.cols)
		{
			rand_value = (double)ml_fast_rand() / 32767;
			((double **)weight->table)[i.rows][i.cols] = rand_value;
		}
	}
}

void	bias_weight_init(
				const size_t id,
				t_weight_bias *const weight_bias,
				t_name *const row_name_array,
				const t_weigth_init_mode weigth_init_mode)
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
	if (weigth_init_mode == E_RAND_0_TO_1)
		set_start_values(weight_bias->weight);
	return ;
}
