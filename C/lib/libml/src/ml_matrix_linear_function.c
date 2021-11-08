/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix_linear_function.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:45:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/08 12:36:42 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ml_matrix_linear_function(
						const t_matrix *const x,
						const t_matrix *const a,
						const t_vector *const b,
						const t_matrix *const y)
{
	t_size_2d	x_i;
	t_size_2d	y_i;

	ml_matrix_print("X", x);
	ml_matrix_print("A", a);
	ml_vector_print("B", b);
	x_i.cols = -1;
	while (++x_i.cols < x->size.cols)
	{
		y_i.cols = x_i.cols;
		y_i.rows = -1;
		while (++y_i.rows < y->size.rows)
		{
			x_i.rows = -1;
			while (++x_i.rows < x->size.rows)
			{
				((double **)y->table)[y_i.rows][y_i.cols]
					+= ((double **)a->table)[y_i.rows][x_i.rows]
					* ((double **)x->table)[x_i.rows][x_i.cols];
			}
			((double **)y->table)[y_i.rows][y_i.cols]
				+= ((double *)b->data)[y_i.rows];
		}
	}
	return ;
}
