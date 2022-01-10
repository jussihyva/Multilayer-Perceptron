/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strext.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:19:44 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/10 13:21:38 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	ft_strext(char **const str, const char *const str_ext)
{
	char	*orig_str;

	orig_str = *str;
	*str = ft_strjoin(*str, str_ext);
	ft_strdel(&orig_str);
	return ;
}
