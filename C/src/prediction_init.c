/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prediction_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhani <juhani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:44:14 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/23 13:21:31 by juhani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

t_prediction	*prediction_init(const int argc, const char *const *const argv)
{
	t_prediction		*prediction;
	const t_cmd_args	*cmd_args;

	prediction = ft_memalloc(sizeof(*prediction));
	prediction->argc_argv.argc = argc;
	prediction->argc_argv.argv = argv;
	prediction->argc_argv.opt_pars = ft_strdup("L:hl");
	prediction->argc_argv.mandatory_params = 1;
	prediction->arg_parser = ft_arg_parser_init(&prediction->argc_argv,
			arg_init, arg_analyze, arg_usage_prediction);
	prediction->cmd_args = ft_arg_parser(prediction->arg_parser);
	cmd_args = prediction->cmd_args;
	prediction->grad_descent_attr
		= grad_descent_attr_initialize(cmd_args->dataset_file,
			cmd_args->weight_bias_file, &cmd_args->hyper_params);
	return (prediction);
}
