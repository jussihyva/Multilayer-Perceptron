/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_influxdb_remove.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:01:36 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/17 11:02:50 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	ft_influxdb_remove(const t_tcp_connection **influxdb_connection)
{
	if (*influxdb_connection)
	{
		SSL_shutdown((*influxdb_connection)->ssl_bio);
		SSL_free((*influxdb_connection)->ssl_bio);
		SSL_CTX_free((*influxdb_connection)->ctx);
		ft_memdel((void **)influxdb_connection);
	}
	return ;
}
