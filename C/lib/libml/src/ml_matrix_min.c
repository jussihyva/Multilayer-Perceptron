/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix_min.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:44:17 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/17 16:58:29 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

const t_vector	*ml_matrix_min(const t_matrix *const matrix)
{
	t_size_2d			i;
	const t_vector		*min_vector;

	min_vector = ml_vector_create(matrix->size.rows);
	ml_vector_set(min_vector, DBL_MAX);
	i.rows = -1;
	while (++i.rows < matrix->size.rows)
	{
		i.cols = -1;
		while (++i.cols < matrix->size.cols)
		{
			((double *)min_vector->data)[i.rows]
				= ft_min_double(((double **)matrix->table)[i.rows][i.cols],
					((double *)min_vector->data)[i.rows]);
		}
	}
	return (min_vector);
}
