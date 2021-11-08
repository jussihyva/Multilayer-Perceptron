/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix_cost.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:56:31 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/08 13:17:30 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ml_matrix_cost(
					const t_matrix *const y,
					const t_matrix *const y_hat,
					t_vector *const cost)
{
	t_size_2d	size;
	double		**y_table;
	double		**y_hat_table;
	double		*cost_data;
	double		value;

	y_table = (double **)y->table;
	y_hat_table = (double **)y_hat->table;
	cost_data = (double *)cost->data;
	size.rows = -1;
	while (++size.rows < y_hat->size.rows)
	{
		size.cols = -1;
		while (++size.cols < y_hat->size.cols)
		{
			if (y_table[size.rows][size.cols] == 1)
				value = y_hat_table[size.rows][size.cols];
			else
				value = 1 - y_hat_table[size.rows][size.cols];
			cost_data[size.rows] += -log(value);
		}
		cost_data[size.rows] /= y_hat->size.cols;
	}
	return ;
}
