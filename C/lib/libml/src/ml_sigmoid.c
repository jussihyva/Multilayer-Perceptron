/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_sigmoid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:30:01 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/07 13:44:52 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ml_sigmoid(const t_matrix *const z, t_matrix *const y)
{
	double		*z_ptr;
	double		*y_ptr;
	double		*y_end_ptr;

	y_end_ptr = (double *)y->data + y->size.rows * y->size.cols;
	z_ptr = (double *)z->data;
	y_ptr = (double *)y->data;
	while (y_ptr < y_end_ptr)
	{
		*y_ptr = 1 / (1 + exp(-(*z_ptr)));
		z_ptr++;
		y_ptr++;
	}
	return ;
}
