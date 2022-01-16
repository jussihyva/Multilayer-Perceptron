/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_analyze.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:07:51 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/16 21:15:29 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	check_number_of_mandatory_variables(t_arg_parser *arg_parser)
{
	static t_bool	is_num_of_mandatory_variables_valid = E_FALSE;
	size_t			num_of_mandatory_variables;

	if (!is_num_of_mandatory_variables_valid)
	{
		num_of_mandatory_variables = arg_parser->argc_argv->argc
			- arg_parser->argc_argv->i;
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
	arg = arg_parser->argc_argv->argv[arg_parser->argc_argv->i];
	if ((arg_parser->argc_argv->argc - arg_parser->argc_argv->i) == 1)
		cmd_args->dataset_file = (const char *)ft_strdup(arg);
	else
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
		arg_param_save_short(cmd_args, opt, arg_parser);
	else
		input_param_mandatory_validate(cmd_args, opt, arg_parser);
	return ;
}
