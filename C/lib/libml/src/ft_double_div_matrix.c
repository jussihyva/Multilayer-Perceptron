/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_div_matrix.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:15:48 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/04 16:22:17 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ft_double_div_matrix(
						const double value,
						const t_matrix *const matrix,
						t_matrix *const new_matrix)
{
	t_matrix_size	i;
	double			**values;
	double			**new_values;

	values = (double **)matrix->values;
	new_values = (double **)new_matrix->values;
	i.rows = -1;
	while (++i.rows < matrix->size.rows)
	{
		i.columns = -1;
		while (++i.columns < matrix->size.columns)
			new_values[i.rows][i.columns] = value / values[i.rows][i.columns];
	}
	return ;
}