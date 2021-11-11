/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_attributes_remove.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:08:39 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/11 20:09:21 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "training.h"

void	file_attributes_remove(t_file_attributes **file_attributes)
{
	size_t		i;

	i = -1;
	while (++i < (*file_attributes)->rows)
	{
		ft_strarraydel(&(*file_attributes)->row_array[i]);
	}
	ft_memdel((void **)&(*file_attributes)->row_array);
	ft_memdel((void **)file_attributes);
	return ;
}
