/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_memory_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 09:59:49 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/27 00:06:53 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	reset_elem(t_list elem)
{
	char	*s;

	s = (char *)elem.content;
	if (elem.content_size)
		ft_strdel(&s);
	return ;
}

static void	del_o_string(t_substring *substring)
{
	reset_elem(substring->o_string.pre_filler);
	reset_elem(substring->o_string.sign);
	reset_elem(substring->o_string.prefix);
	reset_elem(substring->o_string.zero_filler);
	reset_elem(substring->o_string.parameter);
	reset_elem(substring->o_string.post_filler);
}

void	del_substring(void *content, size_t size)
{
	t_substring		*substring;

	(void)size;
	substring = (t_substring *)content;
	ft_strdel(&substring->input_string);
	if (substring->formatter_list)
		ft_lstdel(&substring->formatter_list, *del_formatter);
	del_o_string(substring);
	return ;
}
