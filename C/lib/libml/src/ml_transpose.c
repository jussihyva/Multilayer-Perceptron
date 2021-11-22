/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_transpose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:31:07 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/22 14:36:34 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ml_transpose(
				const t_matrix *const matrix,
				const t_matrix *const transposed)
{
	t_size_2d	i;

	i.rows = -1;
	while (++i.rows < transposed->size.rows)
	{
		i.cols = -1;
		while (++i.cols < transposed->size.cols)
			((double **)transposed->table)[i.rows][i.cols]
				= ((double **)matrix->table)[i.cols][i.rows];
	}
	return ;
}
