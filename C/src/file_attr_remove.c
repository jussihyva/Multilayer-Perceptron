/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_attr_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:08:39 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/22 12:46:59 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	file_attr_remove(t_file_attr **file_attr)
{
	size_t		i;

	if (*file_attr)
	{
		i = -1;
		while (++i < (*file_attr)->rows)
			ft_strarraydel(&(*file_attr)->row_array[i], 0);
		ft_memdel((void **)&(*file_attr)->row_array);
		ft_memdel((void **)file_attr);
	}
	return ;
}
