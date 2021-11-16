/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gettime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:11:43 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/16 14:12:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static time_t	convert_timespec_to_ms(struct timespec *utc_timespec)
{
	time_t		utc_time_ms;
	double		ms;

	utc_time_ms = utc_timespec->tv_sec * 1000;
	ms = round(utc_timespec->tv_nsec / 1.0e6);
	if (ms > 999)
	{
		utc_time_ms++;
		ms = 0;
	}
	utc_time_ms += ms;
	return (utc_time_ms);
}

#if DARWIN

time_t	ft_gettime(void)
{
	struct timespec		utc_timespec;
	time_t				utc_time_ms;

	clock_gettime(CLOCK_REALTIME, &utc_timespec);
	utc_time_ms = convert_timespec_to_ms(&utc_timespec);
	return (utc_time_ms);
}
#else

time_t	ft_gettime(void)
{
	struct timespec		utc_timespec;
	time_t				utc_time_ms;

	clock_gettime(_POSIX_MONOTONIC_CLOCK, &utc_timespec);
	utc_time_ms = convert_timespec_to_ms(&utc_timespec);
	return (utc_time_ms);
}
#endif
