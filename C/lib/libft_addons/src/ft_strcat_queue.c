/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_queue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:49:42 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/16 12:50:19 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

const char	*ft_strcat_queue(
					t_queue *const queue,
					const size_t string_length)
{
	char		*str;
	const char	*sub_str;

	str = ft_strnew(string_length);
	while (!ft_is_queue_empty(queue))
	{
		sub_str = ft_dequeue(queue);
		ft_strcat(str, sub_str);
		ft_strdel((char **)&sub_str);
	}
	return (str);
}
