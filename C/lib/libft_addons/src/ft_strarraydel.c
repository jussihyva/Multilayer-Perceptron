/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarraydel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 13:47:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/22 12:47:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	ft_strarraydel(const char ***const array, const size_t len)
{
	const char	*ptr;
	size_t		i;

	i = 0;
	if (*array)
	{
		while (i < len || (!len && (*array)[i]))
		{
			ptr = (*array)[i];
			ft_strdel((char **)&ptr);
			i++;
		}
		ft_memdel((void **)array);
	}
	return ;
}
