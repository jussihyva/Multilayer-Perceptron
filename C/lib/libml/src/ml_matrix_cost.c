/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix_cost.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:56:31 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/07 14:40:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ml_matrix_cost(
					t_vector *const y,
					const t_matrix *const y_hat,
					t_vector *const cost_vector)
{
	t_size_2d	size;
	double		*data;
	double		value;

	data = (double *)y->data;
	size.rows = -1;
	while (++size.rows < y_hat->size.rows)
	{
		size.cols = -1;
		while (++size.cols < y_hat->size.cols)
		{
			if (data[size.rows] == 1)
				value = ((double **)y_hat->table)[size.rows][size.cols];
			else
				value = 1 - ((double **)y_hat->table)[size.rows][size.cols];
			((double *)cost_vector->data)[size.rows] += -log(value);
		}
		((double *)cost_vector->data)[size.rows] /= y_hat->size.cols;
	}
	return ;
}
