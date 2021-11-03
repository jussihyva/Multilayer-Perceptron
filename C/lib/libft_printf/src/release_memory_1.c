/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_memory_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 17:35:39 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/26 23:39:20 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	del_formatter(void *content, size_t size)
{
	(void)size;
	(void)content;
	return ;
}

static void	del_converter(void *content, size_t size)
{
	(void)size;
	(void)content;
	return ;
}

static void	del_param_type(void *content, size_t size)
{
	(void)size;
	(void)content;
	return ;
}

void	release_memory(t_list **substring_list, t_list **converter_list,
									t_list **formatter_list, t_list **type_list)
{
	ft_lstdel(substring_list, *del_substring);
	ft_memdel((void **)&substring_list);
	ft_lstdel(converter_list, *del_converter);
	ft_memdel((void **)&converter_list);
	ft_lstdel(formatter_list, *del_formatter);
	ft_memdel((void **)&formatter_list);
	ft_lstdel(type_list, *del_param_type);
	ft_memdel((void **)&type_list);
	return ;
}
