/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_influxdb_connect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 13:20:07 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/09 15:49:52 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static void	set_client_socket_params(const int socket_fd)
{
	t_timeval		timeout;
	int				on;

	timeout.tv_sec = 0;
	timeout.tv_usec = 1;
	on = 1;
	setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
	setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
		sizeof(timeout));
	return ;
}

t_tcp_connection	*ft_influxdb_connect(
					const char *const host_name,
					const char *const port_number,
					const t_connection_protocol influxdb_connection_protocol)
{
	SSL_CTX				*ctx;
	int					socket_fd;
	char				*cert_file;
	char				*private_key_file;
	t_tcp_connection	*tcp_connection;

	ft_openssl_init();
	cert_file = ft_file_create(ft_home_dir(), PEM_CERT_FILE);
	FT_LOG_INFO("Cert: %s", cert_file);
	private_key_file = ft_file_create(ft_home_dir(), PEM_PRIVTE_KEY_FILE);
	FT_LOG_INFO("Private key: %s", private_key_file);
	ctx = ft_openssl_init_client(cert_file, private_key_file, &socket_fd,
			influxdb_connection_protocol);
	tcp_connection = ft_openssl_connect(host_name, port_number, socket_fd, ctx);
	if (tcp_connection)
		set_client_socket_params(socket_fd);
	else
	{
		SSL_CTX_free(ctx);
		FT_LOG_WARN("Connection setup to Influxdb failed!");
	}
	ft_strdel(&cert_file);
	ft_strdel(&private_key_file);
	return (tcp_connection);
}
