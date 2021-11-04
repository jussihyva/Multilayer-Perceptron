/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:56:58 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/04 16:06:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

t_matrix	*ft_matrix_create(
						size_t size,
						const size_t rows,
						const size_t columns)
{
	t_matrix	*matrix;
	size_t		i;

	matrix = ft_memalloc(sizeof(*matrix));
	matrix->values = (void **)ft_memalloc(sizeof(*matrix->values) * rows);
	i = -1;
	while (++i < rows)
		matrix->values[i] = ft_memalloc(size * columns);
	matrix->size.rows = rows;
	matrix->size.columns = columns;
	return (matrix);
}
