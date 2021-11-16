/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_analyze.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:07:51 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/16 19:14:55 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static t_logging_level	set_logging_level(const t_argc_argv *const argc_argv)
{
	const char			*arg;
	t_logging_level		logging_level;

	arg = (*argc_argv->argv)[argc_argv->i];
	logging_level = ft_logging_level_param_validate(arg);
	ft_log_set_level(logging_level);
	return (logging_level);
}

static void	check_number_of_mandatory_variables(t_argc_argv *argc_argv)
{
	static t_bool	is_num_of_mandatory_variables_valid = E_FALSE;
	size_t			num_of_mandatory_variables;

	if (!is_num_of_mandatory_variables_valid)
	{
		num_of_mandatory_variables = *argc_argv->argc - argc_argv->i;
		if (num_of_mandatory_variables == 2)
			is_num_of_mandatory_variables_valid = E_TRUE;
		else
			usage_print();
	}
	return ;
}

static void	input_param_mandatory_validate(
								t_cmd_args *const cmd_args,
								char opt,
								t_argc_argv *argc_argv)
{
	const char		*arg;
	const char		*dataset_file_path;

	(void)opt;
	(void)cmd_args;
	check_number_of_mandatory_variables(argc_argv);
	arg = (*argc_argv->argv)[argc_argv->i];
	if (((*argc_argv->argc) - argc_argv->i) == 1)
	{
		dataset_file_path = (const char *)ft_strdup(arg);
	}
	else
		usage_print();
	return ;
}

static void	input_param_save_short(
								t_cmd_args *const cmd_args,
								char opt,
								t_argc_argv *argc_argv)
{
	t_hyper_parameters	*hyper_parameters;

	hyper_parameters = &cmd_args->hyper_parameters;
	if (opt == 'L')
		cmd_args->logging_level = set_logging_level(argc_argv);
	else if (opt == 'S')
		cmd_args->is_influxdb = E_TRUE;
	// else if (opt == 'A')
	// 	hyper_parameters->learning_rate = set_learning_rate(argc_argv);
	// else if (opt == 'I')
	// 	hyper_parameters->iterations = set_number_of_iteration_loops(argc_argv);
	else if (opt == 'l')
		cmd_args->print_leaks = E_TRUE;
	else if (opt == 'h')
		usage_print();
	return ;
}

void	arg_analyze(
					void *const input_params,
					char opt, t_argc_argv *argc_argv,
					t_cmd_param_type cmd_param_type)
{
	if (cmd_param_type == E_OPTIONAL_SHORT)
		input_param_save_short(input_params, opt, argc_argv);
	else
		input_param_mandatory_validate(input_params, opt, argc_argv);
	return ;
}
