/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_logging_5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 09:07:03 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/16 14:26:48 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

int	ft_log_add_fd(int *fd, int level)
{
	return (ft_log_add_callback(file_callback, (void *)fd, level));
}

void	ft_log_trace(const char *file, const int line, const char *fmt, ...)
{
	t_log_event				event;

	if (is_logging_function_activated())
	{
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
	}
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

	if (is_logging_function_activated())
	{
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
	}
	else
	{
		ft_printf("FATAL ERROR. Program is stopped!\n");
		exit(42);
	}
	return ;
}
