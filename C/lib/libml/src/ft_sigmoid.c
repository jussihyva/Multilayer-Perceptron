/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigmoid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:30:01 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/04 19:00:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

const t_matrix	*ft_sigmoid(const t_matrix *const input)
{
	t_matrix			*exp;
	t_matrix			*add;
	t_matrix			*div;
	const t_matrix_size	*size;

	size = &input->size;
	exp = ft_matrix_create(sizeof(double), input->size.rows, size->columns);
	add = ft_matrix_create(sizeof(double), input->size.rows, size->columns);
	div = ft_matrix_create(sizeof(double), input->size.rows, size->columns);
	ft_matrix_exp(input, exp, E_MINUS);
	ft_matrix_add_double(exp, 1, add);
	ft_matrix_remove(&exp);
	ft_double_div_matrix(1, add, div);
	ft_matrix_remove(&add);
	return (div);
}
