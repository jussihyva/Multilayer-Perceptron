/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_argmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:54:53 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/10 23:57:19 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ml_argmax(
			const t_matrix *const matrix,
			const t_vector *const argmax,
			const t_vector *argmax_values)
{
	t_size_2d		i;
	double			value;

	ml_vector_set(argmax_values, DBL_MIN);
	i.cols = -1;
	while (++i.cols < matrix->size.cols)
	{
		i.rows = -1;
		while (++i.rows < matrix->size.rows)
		{
			value = ((double **)matrix->table)[i.rows][i.cols];
			if (((double *)argmax_values->data)[i.cols] < value)
			{
				((double *)argmax_values->data)[i.cols] = value;
				((double *)argmax->data)[i.cols] = i.rows;
			}
		}
	}
	return ;
}
