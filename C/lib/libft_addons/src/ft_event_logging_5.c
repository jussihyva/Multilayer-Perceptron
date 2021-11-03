/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_logging_5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 09:07:03 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/06 11:19:51 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static t_logging_params		*g_logging_params;

void	logging_params_5_set(t_logging_params *logging_params)
{
	g_logging_params = logging_params;
	return ;
}

int	ft_log_add_fd(int *fd, int level)
{
	return (ft_log_add_callback(file_callback, (void *)fd, level));
}

void	ft_log_trace(const char *file, const int line, const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = file;
	event.line = line;
	event.level = LOG_TRACE;
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

void	unlock(void)
{
	if (g_logging_params->lock)
	{
		g_logging_params->lock(1, g_logging_params->udata);
	}
}

void	ft_log_fatal(const char *file, const int line, const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = file;
	event.line = line;
	event.level = LOG_FATAL;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_logging_params->quiet && event.level >= g_logging_params->level)
	{
		va_start(event.ap, fmt);
		stdout_callback(&event);
		va_end(event.ap);
		exit(42);
	}
	execute_logging_extensions(&event, fmt);
	unlock();
	return ;
}
