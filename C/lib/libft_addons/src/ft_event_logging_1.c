/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_logging_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 10:22:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/06 10:21:32 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static t_logging_params		*g_logging_params;

void	ft_logging_params_set(
						const char **level_strings,
						const char **level_colors)
{
	g_logging_params
		= (t_logging_params *)ft_memalloc(sizeof(*g_logging_params));
	g_logging_params->level_strings = level_strings;
	g_logging_params->level_colors = level_colors;
	logging_params_2_set(g_logging_params);
	logging_params_3_set(g_logging_params);
	logging_params_4_set(g_logging_params);
	logging_params_5_set(g_logging_params);
	return ;
}

void	ft_logging_params_release(void)
{
	int		i;

	i = -1;
	while (++i < MAX_LOGGING_EXTENSIONS)
	{
		if (g_logging_params->logging_extensions[i])
			ft_memdel((void **)&g_logging_params->logging_extensions[i]);
	}
	ft_memdel((void **)&g_logging_params);
	return ;
}

void	ft_log_debug(const char *file, const int line, const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = file;
	event.line = line;
	event.level = LOG_DEBUG;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_logging_params->quiet && event.level >= g_logging_params->level)
	{
		va_start(event.ap, fmt);
		stdout_callback(&event);
		va_end(event.ap);
	}
	execute_logging_extensions(&event, fmt);
	unlock();
	return ;
}

void	ft_log_info(const char *file, const int line, const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = file;
	event.line = line;
	event.level = LOG_INFO;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_logging_params->quiet && event.level >= g_logging_params->level)
	{
		va_start(event.ap, fmt);
		stdout_callback(&event);
		va_end(event.ap);
	}
	execute_logging_extensions(&event, fmt);
	unlock();
	return ;
}

void	ft_log_warn(const char *file, const int line, const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = file;
	event.line = line;
	event.level = LOG_WARN;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_logging_params->quiet && event.level >= g_logging_params->level)
	{
		va_start(event.ap, fmt);
		stdout_callback(&event);
		va_end(event.ap);
	}
	execute_logging_extensions(&event, fmt);
	unlock();
	return ;
}
