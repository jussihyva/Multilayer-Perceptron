/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_vector_rand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:47:17 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/07 13:52:30 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ml_vector_rand(t_vector *const vector, const int min, const int max)
{
	int			range;
	double		value;
	double		*data_ptr;
	double		*end_ptr;

	range = max - min;
	data_ptr = vector->data;
	end_ptr = data_ptr + vector->size;
	while (data_ptr < end_ptr)
	{
		value = (ml_fast_rand() % range) + min;
		*data_ptr = value;
		data_ptr++;
	}
	return ;
}
