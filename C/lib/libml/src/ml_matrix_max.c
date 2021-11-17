/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix_max.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:03:10 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/17 16:58:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

const t_vector	*ml_matrix_max(const t_matrix *const matrix)
{
	t_size_2d			i;
	const t_vector		*max_vector;

	max_vector = ml_vector_create(matrix->size.rows);
	ml_vector_set(max_vector, DBL_MIN);
	i.rows = -1;
	while (++i.rows < matrix->size.rows)
	{
		i.cols = -1;
		while (++i.cols < matrix->size.cols)
		{
			((double *)max_vector->data)[i.rows]
				= ft_max_double(((double **)matrix->table)[i.rows][i.cols],
					((double *)max_vector->data)[i.rows]);
		}
	}
	return (max_vector);
}
