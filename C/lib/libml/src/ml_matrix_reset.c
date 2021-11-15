/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix_reset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:58:18 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/15 13:01:30 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ml_matrix_reset(t_matrix *const matrix)
{
	ft_bzero(matrix->data, sizeof(double) * matrix->size.rows
		* matrix->size.cols);
	return ;
}
