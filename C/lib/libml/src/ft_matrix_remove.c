/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:06:48 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/05 17:19:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ft_matrix_remove(t_matrix **matrix)
{
	ft_memdel((void **)&(*matrix)->table);
	ft_memdel((void **)&(*matrix)->data);
	ft_memdel((void **)matrix);
	return ;
}
