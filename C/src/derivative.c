/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   derivative.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:03:59 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/15 13:05:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	calculate_derivative_z(
					const t_matrix *const y_hat,
					const t_matrix *const y,
					t_vector *const derivative_z)
{
	t_size_2d	i;
	double		**table_y;
	double		**table_y_hat;
	double		*data_z;

	ml_vector_reset(derivative_z);
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
	return ;
}

void	calculate_derivative_w(
						const t_matrix *const x,
						const t_vector *const derivative_z,
						t_matrix *const derivative_w)
{
	t_size_2d	i_w;
	t_size_2d	i_x;
	double		**table_w;

	ml_matrix_reset(derivative_w);
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
	return ;
}

void	calculate_derivative_b(
					const t_vector *const derivative_z,
					t_vector *const derivative_b)
{
	double		*data_b;

	ml_vector_reset(derivative_b);
	data_b = (double *)derivative_b->data;
	ft_memcpy(derivative_b->data, derivative_z->data,
		sizeof(double) * derivative_b->size);
	return ;
}
