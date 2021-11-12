/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix_linear_function.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:45:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/12 15:44:20 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ml_matrix_linear_function(
						const t_matrix *const x,
						const t_matrix *const w,
						const t_vector *const b,
						const t_matrix *const z)
{
	size_t		x_row;
	size_t		x_col;
	size_t		z_row;

	// ml_matrix_print("X", x);
	ml_matrix_print("Weight", w);
	ml_vector_print("Bias", b);
	x_col = -1;
	while (++x_col < x->size.cols)
	{
		z_row = -1;
		while (++z_row < z->size.rows)
		{
			x_row = -1;
			while (++x_row < x->size.rows)
			{
				((double **)z->table)[z_row][x_col]
					+= ((double **)w->table)[z_row][x_row]
					* ((double **)x->table)[x_row][x_col];
			}
		}
		z_row = -1;
		while (++z_row < z->size.rows)
		{
			((double **)z->table)[z_row][x_col]
				+= ((double *)b->data)[z_row];
		}
	}
	return ;
}
