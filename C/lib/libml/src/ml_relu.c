/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_relu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:51:34 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/03 15:17:14 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ml_relu(const t_matrix *const z, t_matrix *const y)
{
	double		*z_ptr;
	double		*y_ptr;
	double		*y_end_ptr;

	y_end_ptr = (double *)y->data + y->size.rows * y->size.cols;
	z_ptr = (double *)z->data;
	y_ptr = (double *)y->data;
	while (y_ptr < y_end_ptr)
	{
		*y_ptr = ft_max_double(EPSILON, *z_ptr);
		z_ptr++;
		y_ptr++;
	}
	return ;
}
