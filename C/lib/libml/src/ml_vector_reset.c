/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_vector_reset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:58:53 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/15 13:00:22 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ml_vector_reset(t_vector *const vector)
{
	ft_bzero(vector->data, sizeof(double) * vector->size);
	return ;
}
