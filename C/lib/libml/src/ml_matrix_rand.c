/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix_rand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 11:21:38 by jkauppi           #+#    #+#             */
/*   Updated: 2022/07/11 11:50:17 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ml_matrix_rand(t_matrix *const matrix, const int min, const int max,
					const t_bool fixed)
{
	int			range;
	double		value;
	double		*data_ptr;
	double		*end_ptr;

	range = max - min;
	data_ptr = matrix->data;
	end_ptr = data_ptr + matrix->size.rows * matrix->size.cols;
	while (data_ptr < end_ptr)
	{
		value = (ml_fast_rand(fixed) % range) + min;
		*data_ptr = value;
		data_ptr++;
	}
	return ;
}
