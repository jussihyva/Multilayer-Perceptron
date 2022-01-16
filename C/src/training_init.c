/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:34:10 by juhani            #+#    #+#             */
/*   Updated: 2022/01/16 20:59:31 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static t_database	g_database;

const t_tcp_connection	*get_database_connection(void)
{
	return (g_database.connection);
}

t_training	*training_init(const int argc, const char *const *const argv)
{
	t_training				*training;
	const t_cmd_args		*cmd_args;

	training = ft_memalloc(sizeof(*training));
	training->argc_argv.argc = argc;
	training->argc_argv.argv = argv;
	training->argc_argv.opt_pars = ft_strdup("L:hlA:E:s:w:M:t:");
	training->argc_argv.mandatory_params = 1;
	training->arg_parser = ft_arg_parser_init(&training->argc_argv,
			arg_init_train, arg_analyze, arg_usage_training);
	training->cmd_args = ft_arg_parser(training->arg_parser);
	cmd_args = training->cmd_args;
	training->input_data = input_data_init(cmd_args->dataset_file,
			&training->cmd_args->hyper_params.split_order);
	training->grad_descent_attr
		= grad_descent_attr_initialize(training->input_data,
			cmd_args->weight_bias_file, &cmd_args->hyper_params);
	training->grad_descent_attr->influxdb_connection
		= ft_influxdb_connect("127.0.0.1", "8086", E_TLS);
	g_database.connection = training->grad_descent_attr->influxdb_connection;
	return (training);
}
