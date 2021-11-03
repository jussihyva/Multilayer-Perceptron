/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_logging_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 08:21:58 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/13 12:14:27 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static t_logging_params	*g_logging_params;

void	logging_params_2_set(t_logging_params *loging_params)
{
	g_logging_params = loging_params;
	return ;
}

void	execute_logging_extensions(t_log_event *event, const char *fmt, ...)
{
	size_t					i;
	t_logging_extension		*logging_extension;

	i = -1;
	while (++i < MAX_LOGGING_EXTENSIONS)
	{
		if (g_logging_params->logging_extensions[i])
		{
			logging_extension = g_logging_params->logging_extensions[i];
			if (event->level >= logging_extension->level)
			{
				event->additional_event_data
					= logging_extension->additional_event_data;
				va_start(event->ap, fmt);
				logging_extension->fn(event);
				va_end(event->ap);
			}
		}
	}
	return ;
}

void	ft_log_error(const char *file, const int line, const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = file;
	event.line = line;
	event.level = LOG_ERROR;
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

t_logging_level	ft_logging_level_param_validate(const char *level_str)
{
	char				*endptr;
	t_logging_level		event_logging_level;

	errno = 0;
	event_logging_level = (t_logging_level)ft_strtoi(level_str, &endptr, 10);
	if (event_logging_level >= 5 || event_logging_level < 0
		|| *endptr != '\0' || errno != 0)
	{
		ft_printf("Value of cmd line attribute -L (%s) is not valid\n",
			level_str);
		exit(42);
	}
	return (event_logging_level);
}

t_logging_level	ft_log_get_level(void)
{
	return (g_logging_params->level);
}
