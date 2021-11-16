/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:23:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/16 19:21:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// while [ condition ]; do time ./training ; done

#include "multilayer_perceptron.h"

int	main(int argc, char **argv)
{
	t_grad_descent_attr		*grad_descent_attr;
	t_arg_parser			*arg_parser;
	t_argc_argv				argc_argv;
	const t_cmd_args		*cmd_args;

	argc_argv.argc = (const int *)&argc;
	argc_argv.argv = (const char ***)&argv;
	arg_parser = ft_arg_parser_init(&argc_argv, arg_init, arg_analyze,
			usage_print);
	cmd_args = ft_arg_parser(arg_parser);
	grad_descent_attr = grad_descent_attr_initialize();
	grad_descent_attr->connection = ft_influxdb_connect("127.0.0.1", "8086",
			E_TLS);
	grad_descent(grad_descent_attr);
	grad_descent_attr_remove(&grad_descent_attr);
	return (0);
}
