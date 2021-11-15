/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:23:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/15 17:41:20 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// while [ condition ]; do time ./training ; done

#include "multilayer_perceptron.h"

int	main(void)
{
	const t_tcp_connection		*connection;
	t_grad_descent_attr			*grad_descent_attr;

	connection = ft_influxdb_connect("127.0.0.1", "8086", E_TLS);
	return (0);
	grad_descent_attr = grad_descent_attr_initialize();
	grad_descent(grad_descent_attr);
	grad_descent_attr_remove(&grad_descent_attr);
	return (0);
}
