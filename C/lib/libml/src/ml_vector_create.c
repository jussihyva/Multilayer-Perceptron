/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_vector_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:14:29 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/15 13:24:02 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

t_vector	*ml_vector_create(const size_t length)
{
	t_vector	*vector;

	vector = ft_memalloc(sizeof(*vector));
	vector->data = ft_memalloc(sizeof(double) * length);
	vector->name_array = ft_memalloc(sizeof(*vector->name_array) * length);
	vector->size = length;
	return (vector);
}
