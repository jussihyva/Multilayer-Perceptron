/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bias_weight_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 10:17:34 by jkauppi           #+#    #+#             */
/*   Updated: 2022/07/11 12:12:19 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	set_start_values(t_matrix *const weight, const t_bool fixed)
{
	t_size_2d		i;
	double			rand_value;

	i.rows = -1;
	while (++i.rows < weight->size.rows)
	{
		i.cols = -1;
		while (++i.cols < weight->size.cols)
		{
			rand_value = (double)ml_fast_rand(fixed) / 32767;
			((double **)weight->table)[i.rows][i.cols] = rand_value;
		}
	}
}

void	bias_weight_init(
				const t_size_2d size,
				t_weight_bias *const weight_bias,
				t_name *const row_name_array,
				const t_weight_init_mode weight_init_mode)
{
	t_bool		fixed;

	weight_bias->weight = ml_matrix_create(size);
	weight_bias->bias = ml_vector_create(size.rows);
	if (row_name_array)
		weight_bias->weight->col_name_array = row_name_array;
	if (weight_init_mode == E_RAND_0_TO_1)
		fixed = E_FALSE;
	else
		fixed = E_TRUE;
	set_start_values(weight_bias->weight, fixed);
	return ;
}
