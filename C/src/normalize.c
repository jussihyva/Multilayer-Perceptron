/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:13:10 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/17 16:23:01 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	calculate(
				t_matrix *const matrix,
				const t_vector *const min,
				const t_vector *const max)
{
	t_size_2d	i;
	double		**table;
	double		*data_min;
	double		*data_max;
	double		range;

	table = (double **)matrix->table;
	data_min = (double *)min->data;
	data_max = (double *)max->data;
	i.rows = -1;
	while (++i.rows < matrix->size.rows)
	{
		i.cols = -1;
		range = data_max[i.rows] - data_min[i.rows];
		while (++i.cols < matrix->size.cols)
		{
			table[i.rows][i.cols] -= data_min[i.rows];
			table[i.rows][i.cols] /= range;
		}
	}
	return ;
}

void	normalize(t_matrix *const matrix)
{
	const t_vector		*min;
	const t_vector		*max;

	min = ml_matrix_min(matrix);
	max = ml_matrix_max(matrix);
	ml_vector_print("MIN", min);
	ml_vector_print("MAX", max);
	calculate(matrix, min, max);
	ml_vector_remove((t_vector **)&min);
	ml_vector_remove((t_vector **)&max);
	return ;
}
