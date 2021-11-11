/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:21:59 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/11 14:22:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	ft_queue_remove(t_queue **queue)
{
	ft_memdel((void **)&(*queue)->in_stack);
	ft_memdel((void **)&(*queue)->out_stack);
	ft_memdel((void **)queue);
	return ;
}
