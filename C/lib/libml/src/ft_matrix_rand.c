/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_rand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 11:21:38 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/07 12:07:06 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

static int	fast_rand(void)
{
	static unsigned int		seed;
	static time_t			timer;

	if (!timer)
	{
		time(&timer);
		seed = (unsigned int)timer;
	}
	seed = 214013 * seed + 2531011;
	return ((seed >> 16) & 0x7FFF);
}

void	ft_matrix_rand(t_matrix *const matrix, const int min, const int max)
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
		value = (fast_rand() % range) + min;
		*data_ptr = value;
		data_ptr++;
	}
	return ;
}
