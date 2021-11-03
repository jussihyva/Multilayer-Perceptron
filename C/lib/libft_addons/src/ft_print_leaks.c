/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_leaks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:07:03 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/30 09:08:52 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

#if DARWIN

void	ft_print_leaks(const char *prog_name)
{
	char	*command;

	command = ft_strjoin("leaks ", prog_name);
	system(command);
	ft_strdel(&command);
	return ;
}
#else

void	ft_print_leaks(const char *prog_name)
{
	(void)prog_name;
	return ;
}
#endif
