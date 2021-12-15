/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:56:58 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/15 13:15:33 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

t_matrix	*ml_matrix_create(const size_t rows, const size_t cols)
{
	t_matrix	*matrix;
	size_t		i;

	matrix = ft_memalloc(sizeof(*matrix));
	matrix->data = ft_memalloc(sizeof(double) * rows * cols);
	matrix->table = ft_memalloc(sizeof(*matrix->table) * rows);
	matrix->row_name_array = ft_memalloc(sizeof(*matrix->row_name_array)
			* rows);
	matrix->col_name_array = ft_memalloc(sizeof(*matrix->col_name_array)
			* cols);
	i = -1;
	while (++i < rows)
		matrix->table[i] = matrix->data + sizeof(double) * i * cols;
	matrix->size.rows = rows;
	matrix->size.cols = cols;
	return (matrix);
}
