/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openssl_connect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:42:37 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/13 11:48:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static void	sockaddr_initialize(
							struct sockaddr_in *const sockaddr,
							const char *const hostname,
							const char *const port)
{
	bzero(sockaddr, sizeof(*sockaddr));
	sockaddr->sin_family = AF_INET;
	sockaddr->sin_port = htons(atoi(port));
	sockaddr->sin_addr.s_addr = inet_addr(hostname);
	return ;
}

static SSL	*tls_setup(const int socket_fd, SSL_CTX *const ctx)
{
	int			error;
	SSL			*ssl_bio;

	ssl_bio = SSL_new(ctx);
	SSL_set_fd(ssl_bio, socket_fd);
	error = SSL_connect(ssl_bio);
	if (error == -1)
	{
		FT_LOG_WARN("SSL connection error: %d", error);
		SSL_free(ssl_bio);
		ssl_bio = NULL;
	}
	return (ssl_bio);
}

t_tcp_connection	*ft_openssl_connect(
									const char *const hostname,
									const char *const port,
									const int socket_fd,
									SSL_CTX *const ctx)
{
	int					error;
	struct sockaddr_in	sockaddr;
	t_tcp_connection	*tcp_connection;

	tcp_connection = NULL;
	sockaddr_initialize(&sockaddr, hostname, port);
	error = connect(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
	if (error != -1)
	{
		tcp_connection = ft_memalloc(sizeof(*tcp_connection));
		tcp_connection->socket_fd = socket_fd;
		tcp_connection->ctx = ctx;
		if (tcp_connection->ctx)
		{
			tcp_connection->ssl_bio = tls_setup(socket_fd, ctx);
			if (!tcp_connection->ssl_bio)
				ft_openssl_rel_conn(&tcp_connection);
		}
	}
	else
		FT_LOG_WARN("Influxdb connection error: %d", error);
	return (tcp_connection);
}
