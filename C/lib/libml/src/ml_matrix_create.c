/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:56:58 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/02 12:27:04 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

t_matrix	*ml_matrix_create(const t_size_2d size)
{
	t_matrix	*matrix;
	size_t		i;

	matrix = ft_memalloc(sizeof(*matrix));
	matrix->data = ft_memalloc(sizeof(double) * size.rows * size.cols);
	matrix->table = ft_memalloc(sizeof(*matrix->table) * size.rows);
	matrix->row_name_array = ft_memalloc(sizeof(*matrix->row_name_array)
			* size.rows);
	matrix->col_name_array = ft_memalloc(sizeof(*matrix->col_name_array)
			* size.cols);
	i = -1;
	while (++i < size.rows)
		matrix->table[i] = matrix->data + sizeof(double) * i * size.cols;
	matrix->size.rows = size.rows;
	matrix->size.cols = size.cols;
	return (matrix);
}
