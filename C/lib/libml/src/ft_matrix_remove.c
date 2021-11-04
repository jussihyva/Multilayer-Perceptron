/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:06:48 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/04 18:07:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ft_matrix_remove(t_matrix **matrix)
{
	size_t		i;

	i = -1;
	while (++i < (*matrix)->size.rows)
		ft_memdel(&(*matrix)->values[i]);
	ft_memdel((void **)&(*matrix)->values);
	ft_memdel((void **)matrix);
	return ;
}
