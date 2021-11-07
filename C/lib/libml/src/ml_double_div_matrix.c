/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_double_div_matrix.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:15:48 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/07 13:43:51 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ml_double_div_matrix(
						const double value,
						const t_matrix *const matrix,
						t_matrix *const new_matrix)
{
	t_size_2d	i;
	double		**values;
	double		**new_values;

	values = (double **)matrix->table;
	new_values = (double **)new_matrix->table;
	i.rows = -1;
	while (++i.rows < matrix->size.rows)
	{
		i.cols = -1;
		while (++i.cols < matrix->size.cols)
			new_values[i.rows][i.cols] = value / values[i.rows][i.cols];
	}
	return ;
}
