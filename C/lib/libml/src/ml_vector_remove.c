/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_vector_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:52:18 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/11 19:55:28 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ml_vector_remove(t_vector **vector)
{
	ft_memdel(&(*vector)->data);
	ft_memdel((void **)vector);
	return ;
}
