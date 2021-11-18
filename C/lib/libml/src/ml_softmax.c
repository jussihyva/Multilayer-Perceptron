/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_softmax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:48:50 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/18 16:23:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

static t_vector	*exp_sum_cal(const t_matrix *const matrix)
{
	t_vector	*exp_sum;
	t_size_2d	i;
	double		value;

	exp_sum = ml_vector_create(matrix->size.cols);
	i.cols = -1;
	while (++i.cols < matrix->size.cols)
	{
		i.rows = -1;
		while (++i.rows < matrix->size.rows)
		{
			value = ((double **)matrix->table)[i.rows][i.cols];
			((double *)exp_sum->data)[i.cols] += exp(value);
		}
	}
	return (exp_sum);
}

void	ml_softmax(const t_matrix *const matrix, const t_matrix *const softmax)
{
	t_size_2d			i;
	double				value;
	const t_vector		*exp_sum;

	exp_sum = exp_sum_cal(matrix);
	i.cols = -1;
	while (++i.cols < matrix->size.cols)
	{
		i.rows = -1;
		while (++i.rows < matrix->size.rows)
		{
			value = ((double **)matrix->table)[i.rows][i.cols];
			((double **)softmax->table)[i.rows][i.cols] = exp(value)
				/ ((double *)exp_sum->data)[i.cols];
		}
	}
	ml_vector_remove((t_vector **)&exp_sum);
	return ;
}
