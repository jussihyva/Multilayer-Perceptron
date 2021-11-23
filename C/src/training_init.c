/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhani <juhani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:34:10 by juhani            #+#    #+#             */
/*   Updated: 2021/11/23 13:04:04 by juhani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

t_training	*training_init(const int argc, const char *const *const argv)
{
	t_training	    	*training;
	const t_cmd_args	*cmd_args;

	training = ft_memalloc(sizeof(*training));
	training->argc_argv.argc = argc;
	training->argc_argv.argv = argv;
	training->argc_argv.opt_pars = ft_strdup("L:hlA:E:");
	training->argc_argv.mandatory_params = 1;
	training->arg_parser = ft_arg_parser_init(&training->argc_argv,
			arg_init, arg_analyze, arg_usage_training);
	training->cmd_args = ft_arg_parser(training->arg_parser);
	cmd_args = training->cmd_args;
	training->grad_descent_attr
		= grad_descent_attr_initialize(cmd_args->dataset_file,
			cmd_args->weight_bias_file, &cmd_args->hyper_params);
	return (training);
}
