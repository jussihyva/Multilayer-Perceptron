/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_param_save.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 21:09:15 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/16 21:18:37 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static t_logging_level	set_logging_level(const t_argc_argv *const argc_argv)
{
	const char			*arg;
	t_logging_level		logging_level;

	arg = argc_argv->argv[argc_argv->i];
	logging_level = ft_logging_level_param_validate(arg);
	ft_log_set_level(logging_level);
	return (logging_level);
}

static void	arg_param_save_short_part_1(
					t_cmd_args *const cmd_args,
					char opt,
					t_arg_parser *arg_parser)
{
	t_hyper_params		*hyper_params;

	hyper_params = &cmd_args->hyper_params;
	if (opt == 'L')
		cmd_args->logging_level = set_logging_level(arg_parser->argc_argv);
	else if (opt == 'S')
		cmd_args->is_influxdb = E_TRUE;
	else if (opt == 'A')
		hyper_params->learning_rate = set_learning_rate(arg_parser->argc_argv);
	else if (opt == 's')
		set_split_mode(arg_parser->argc_argv, &hyper_params->split_order);
	else if (opt == 'w')
		hyper_params->weight_init_mode = set_weight_init_mode(
				arg_parser->argc_argv);
	else if (opt == 'E')
		hyper_params->epochs = set_num_of_epochs(arg_parser->argc_argv);
	return ;
}

void	arg_param_save_short(
					t_cmd_args *const cmd_args,
					char opt,
					t_arg_parser *arg_parser)
{
	t_hyper_params		*hyper_params;

	hyper_params = &cmd_args->hyper_params;
	arg_param_save_short_part_1(cmd_args, opt, arg_parser);
	if (opt == 'M')
		hyper_params->num_of_layers = set_num_of_layers(arg_parser->argc_argv);
	else if (opt == 'l')
		cmd_args->print_leaks = E_TRUE;
	else if (opt == 't')
		cmd_args->dataset_test_file
			= set_dataset_test_file(arg_parser->argc_argv);
	else if (opt == 'h')
		arg_parser->fn_usage_print();
	return ;
}
