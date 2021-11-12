/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   derivative.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:03:59 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/12 20:44:33 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "training.h"

t_vector	*calculate_derivative_of_z(t_matrix *y_hat, t_matrix *y)
{
	t_vector	*derivative_z;
	t_size_2d	i;
	double		**table_y;
	double		**table_y_hat;
	double		*data_z;

	derivative_z = ml_vector_create(y->size.rows);
	table_y = (double **)y->table;
	table_y_hat = (double **)y_hat->table;
	data_z = (double *)derivative_z->data;
	i.rows = -1;
	while (++i.rows < y->size.rows)
	{
		i.cols = -1;
		while (++i.cols < y->size.cols)
		{
			data_z[i.rows] += table_y_hat[i.rows][i.cols]
				- table_y[i.rows][i.cols];
		}
		data_z[i.rows] /= y->size.cols;
	}
	return (derivative_z);
}

t_matrix	*calculate_derivative_of_w(t_matrix *x, t_vector *derivative_z)
{
	t_matrix	*derivative_w;
	t_size_2d	i_w;
	t_size_2d	i_x;
	double		**table_w;

	derivative_w = ml_matrix_create(derivative_z->size, x->size.rows);
	table_w = (double **)derivative_w->table;
	i_w.rows = -1;
	while (++i_w.rows < derivative_w->size.rows)
	{
		i_w.cols = -1;
		while (++i_w.cols < derivative_w->size.cols)
		{
			i_x.cols = -1;
			while (++i_x.cols < x->size.cols)
			{
				table_w[i_w.rows][i_w.cols]
					= ((double **)x->table)[i_w.cols][i_x.cols]
					* ((double *)derivative_z->data)[i_w.rows];
			}
			table_w[i_w.rows][i_w.cols] /= x->size.cols;
		}
	}
	return (derivative_w);
}
