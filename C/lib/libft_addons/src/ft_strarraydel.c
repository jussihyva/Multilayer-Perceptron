/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarraydel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 13:47:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/08 17:53:07 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	ft_strarraydel(const char ***const array)
{
	const char	*ptr;
	size_t		i;

	i = 0;
	while ((*array)[i])
	{
		ptr = (*array)[i];
		ft_strdel((char **)&ptr);
		i++;
	}
	ft_memdel((void **)array);
	return ;
}
