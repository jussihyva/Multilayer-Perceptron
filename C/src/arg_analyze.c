/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_analyze.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:07:51 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/22 11:09:28 by jkauppi          ###   ########.fr       */
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

static void	check_number_of_mandatory_variables(t_arg_parser *arg_parser)
{
	static t_bool	is_num_of_mandatory_variables_valid = E_FALSE;
	size_t			num_of_mandatory_variables;

	if (!is_num_of_mandatory_variables_valid)
	{
		num_of_mandatory_variables = arg_parser->argc_argv.argc
			- arg_parser->argc_argv.i;
		if (num_of_mandatory_variables == 1)
			is_num_of_mandatory_variables_valid = E_TRUE;
		else
			arg_parser->fn_usage_print();
	}
	return ;
}

static void	input_param_mandatory_validate(
								t_cmd_args *const cmd_args,
								char opt,
								t_arg_parser *arg_parser)
{
	const char		*arg;

	(void)opt;
	check_number_of_mandatory_variables(arg_parser);
	arg = arg_parser->argc_argv.argv[arg_parser->argc_argv.i];
	if ((arg_parser->argc_argv.argc - arg_parser->argc_argv.i) == 1)
		cmd_args->dataset_file = (const char *)ft_strdup(arg);
	else
		arg_parser->fn_usage_print();
	return ;
}

static void	input_param_save_short(
								t_cmd_args *const cmd_args,
								char opt,
								t_arg_parser *arg_parser)
{
	t_hyper_parameters	*hyper_parameters;

	hyper_parameters = &cmd_args->hyper_parameters;
	if (opt == 'L')
		cmd_args->logging_level = set_logging_level(&arg_parser->argc_argv);
	else if (opt == 'S')
		cmd_args->is_influxdb = E_TRUE;
	// else if (opt == 'A')
	// 	hyper_parameters->learning_rate = set_learning_rate(argc_argv);
	// else if (opt == 'I')
	// 	hyper_parameters->iterations = set_number_of_iteration_loops(argc_argv);
	else if (opt == 'l')
		cmd_args->print_leaks = E_TRUE;
	else if (opt == 'h')
		arg_parser->fn_usage_print();
	return ;
}

void	arg_analyze(
					void *const cmd_args,
					char opt,
					void *arg_parser,
					t_cmd_param_type cmd_param_type)
{
	if (cmd_param_type == E_OPTIONAL_SHORT)
		input_param_save_short(cmd_args, opt, arg_parser);
	else
		input_param_mandatory_validate(cmd_args, opt, arg_parser);
	return ;
}
