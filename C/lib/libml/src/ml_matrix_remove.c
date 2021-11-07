/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:06:48 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/07 13:44:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ml_matrix_remove(t_matrix **matrix)
{
	ft_memdel((void **)&(*matrix)->table);
	ft_memdel((void **)&(*matrix)->data);
	ft_memdel((void **)matrix);
	return ;
}
