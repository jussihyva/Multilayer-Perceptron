/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_logging_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 08:22:06 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/06 10:24:20 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static t_logging_params	*g_logging_params;

void	logging_params_3_set(t_logging_params *logging_params)
{
	g_logging_params = logging_params;
	return ;
}

void	ft_log_set_lock(t_logging_lock_function fn, void *udata)
{
	g_logging_params->lock = fn;
	g_logging_params->udata = udata;
}

void	ft_log_set_level(int level)
{
	g_logging_params->level = level;
}

void	ft_log_set_quiet(int enable)
{
	g_logging_params->quiet = enable;
}

int	ft_log_add_callback(t_logging_function fn, void *additional_event_data,
																	int level)
{
	t_logging_extension		*logging_extension;
	size_t					i;

	logging_extension
		= (t_logging_extension *)ft_memalloc(sizeof(*logging_extension));
	logging_extension->fn = fn;
	logging_extension->additional_event_data = additional_event_data;
	logging_extension->level = level;
	i = -1;
	while (++i < MAX_LOGGING_EXTENSIONS)
	{
		if (!g_logging_params->logging_extensions[i])
		{
			g_logging_params->logging_extensions[i] = logging_extension;
			return (0);
		}
	}
	return (-1);
}
