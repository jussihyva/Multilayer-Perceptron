/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openssl_rel_conn.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 11:41:51 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/09 15:52:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	ft_openssl_rel_conn(t_tcp_connection **connection)
{
	SSL_free((*connection)->ssl_bio);
	(*connection)->ctx = NULL;
	(*connection)->ssl_bio = NULL;
	ft_memdel((void **)connection);
	return ;
}
