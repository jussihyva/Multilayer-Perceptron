/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:56:58 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/05 17:12:20 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

t_matrix	*ft_matrix_create(
						size_t size,
						const size_t rows,
						const size_t cols)
{
	t_matrix	*matrix;
	size_t		i;

	matrix = ft_memalloc(sizeof(*matrix));
	matrix->data = ft_memalloc(size * rows * cols);
	matrix->table = ft_memalloc(sizeof(*matrix->table) * rows);
	i = -1;
	while (++i < rows)
		matrix->table[i] = matrix->data + size * i * cols;
	matrix->size.rows = rows;
	matrix->size.cols = cols;
	return (matrix);
}
