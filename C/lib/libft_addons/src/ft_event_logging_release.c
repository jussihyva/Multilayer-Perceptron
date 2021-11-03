/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_logging_release.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 10:32:15 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/06 11:17:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	ft_logging_release(const t_logging_data **const logging_data)
{
	int		i;

	i = -1;
	while (++i < 6)
		ft_memdel((void **)&(*logging_data)->level_colors[i]);
	ft_memdel((void **)&(*logging_data)->level_colors);
	i = -1;
	while (++i < 6)
		ft_memdel((void **)&(*logging_data)->level_strings[i]);
	ft_memdel((void **)&(*logging_data)->level_strings);
	ft_memdel((void **)logging_data);
	ft_logging_params_release();
	return ;
}
