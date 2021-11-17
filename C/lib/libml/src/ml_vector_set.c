/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_vector_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:35:51 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/17 16:45:22 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ml_vector_set(const t_vector *const vector, const double value)
{
	size_t		i;

	i = -1;
	while (++i < vector->size)
		((double *)vector->data)[i] = value;
	return ;
}
