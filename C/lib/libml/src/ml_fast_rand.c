/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_fast_rand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:49:25 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/07 13:50:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

int	ml_fast_rand(void)
{
	static unsigned int		seed;
	static time_t			timer;

	if (!timer)
	{
		time(&timer);
		seed = (unsigned int)timer;
	}
	seed = 214013 * seed + 2531011;
	return ((seed >> 16) & 0x7FFF);
}
