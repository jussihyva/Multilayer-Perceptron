/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   derivative.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:03:59 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/15 15:30:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	calculate_derivative_z(
					const t_matrix *const y_hat,
					const t_matrix *const y,
					t_matrix *const derivative_z)
{
	size_t		node_id;
	size_t		example_id;
	double		**table_y;
	double		**table_y_hat;
	double		**table_z;

	table_y = (double **)y->table;
	table_y_hat = (double **)y_hat->table;
	table_z = (double **)derivative_z->table;
	node_id = -1;
	while (++node_id < y->size.rows)
	{
		example_id = -1;
		while (++example_id < y->size.cols)
		{
			table_z[node_id][example_id] = table_y_hat[node_id][example_id]
				- table_y[node_id][example_id];
		}
	}
	return ;
}

void	calculate_derivative_w(
						const t_matrix *const x,
						const t_matrix *const derivative_z,
						t_matrix *const derivative_w)
{
	size_t		node_id;
	size_t		function_id;
	size_t		example_id;
	double		**table_w;

	ml_matrix_reset(derivative_w);
	table_w = (double **)derivative_w->table;
	node_id = -1;
	while (++node_id < derivative_w->size.rows)
	{
		function_id = -1;
		while (++function_id < derivative_w->size.cols)
		{
			example_id = -1;
			while (++example_id < x->size.cols)
			{
				table_w[node_id][function_id]
					+= ((double **)x->table)[function_id][example_id]
					* ((double **)derivative_z->table)[node_id][example_id];
			}
			table_w[node_id][function_id] /= x->size.cols;
		}
	}
	return ;
}

void	calculate_derivative_b(
					const t_matrix *const derivative_z,
					t_vector *const derivative_b)
{
	double		*data_b;
	double		**table_z;
	size_t		node_id;
	size_t		example_id;

	ml_vector_reset(derivative_b);
	data_b = (double *)derivative_b->data;
	table_z = (double **)derivative_z->table;
	node_id = -1;
	while (++node_id < derivative_z->size.rows)
	{
		example_id = -1;
		while (++example_id < derivative_z->size.cols)
			data_b[node_id] += table_z[node_id][example_id];
		data_b[node_id] /= derivative_z->size.cols;
	}
	return ;
}