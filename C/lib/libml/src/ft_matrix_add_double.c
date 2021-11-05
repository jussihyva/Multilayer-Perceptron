/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_add_double.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:56:57 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/05 17:57:58 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	OLD_ft_matrix_add_double(
						const t_matrix *const matrix,
						const double value,
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
			new_values[i.rows][i.cols] = values[i.rows][i.cols] + value;
	}
	return ;
}

void	ft_matrix_add_double(
						const t_matrix *const matrix,
						const double value,
						t_matrix *const new_matrix)
{
	double		*value_ptr;
	double		*new_value_ptr;
	double		*end_ptr;

	end_ptr = (double *)new_matrix->data
		+ new_matrix->size.rows * new_matrix->size.cols;
	value_ptr = (double *)matrix->data;
	new_value_ptr = (double *)new_matrix->data;
	while (new_value_ptr < end_ptr)
	{
		*new_value_ptr = *value_ptr + value;
		new_value_ptr++;
		value_ptr++;
	}
	return ;
}
