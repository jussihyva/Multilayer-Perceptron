/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prediction_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:44:14 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/04 17:41:22 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

t_prediction	*prediction_init(const int argc, const char *const *const argv)
{
	t_prediction		*prediction;
	const t_cmd_args	*cmd_args;
	t_split_order		split_order;

	prediction = ft_memalloc(sizeof(*prediction));
	prediction->argc_argv.argc = argc;
	prediction->argc_argv.argv = argv;
	prediction->argc_argv.opt_pars = ft_strdup("L:hl");
	prediction->argc_argv.mandatory_params = 1;
	prediction->arg_parser = ft_arg_parser_init(&prediction->argc_argv,
			arg_init_predict, arg_analyze, arg_usage_prediction);
	prediction->cmd_args = ft_arg_parser(prediction->arg_parser);
	cmd_args = prediction->cmd_args;
	split_order.split_mode = E_BEGIN;
	split_order.extra_info = 100;
	prediction->input_data = input_data_init(cmd_args->dataset_file,
			&split_order);
	prediction->grad_descent_attr
		= grad_descent_attr_initialize(prediction->input_data,
			cmd_args->weight_bias_file, &cmd_args->hyper_params);
	prediction->grad_descent_attr->influxdb_connection
		= ft_influxdb_connect("127.0.0.1", "8086", E_TLS);
	return (prediction);
}
