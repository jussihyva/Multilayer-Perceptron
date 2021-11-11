/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarray_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:47:36 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/11 13:53:58 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	ft_strarray_print(const char **const array)
{
	size_t		i;

	i = 0;
	while (array[i])
	{
		if (i)
			ft_printf(" ");
		ft_printf("%s", array[i]);
		i++;
	}
	ft_printf("\n");
	return ;
}
