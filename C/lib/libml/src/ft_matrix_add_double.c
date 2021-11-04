/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_add_double.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:56:57 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/04 18:01:17 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ft_matrix_add_double(
						const t_matrix *const matrix,
						const double value,
						t_matrix *const new_matrix)
{
	t_vector_size	i;
	double			**values;
	double			**new_values;

	values = (double **)matrix->values;
	new_values = (double **)new_matrix->values;
	i.rows = -1;
	while (++i.rows < matrix->size.rows)
	{
		i.columns = -1;
		while (++i.columns < matrix->size.columns)
			new_values[i.rows][i.columns] = values[i.rows][i.columns] + value;
	}
	return ;
}
