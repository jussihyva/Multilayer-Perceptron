/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 17:42:28 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/03 12:43:32 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static void	param_error(const char *error_string, const char s)
{
	ft_printf(error_string, s);
	ft_printf("\n");
	exit(42);
	return ;
}

static int	pre_analyse_argument(char *options, char arg,
														t_argc_argv *argc_argv)
{
	char					*opt_ptr;
	int						result;

	opt_ptr = ft_strchr(options, arg);
	if (opt_ptr && arg != ':')
	{
		if (*(opt_ptr + 1) == ':')
		{
			if ((*argc_argv->argc - argc_argv->i) < 2)
				param_error("Missing argument for parameter: -%c", arg);
			argc_argv->i++;
		}
		result = 1;
	}
	else
		result = 0;
	return (result);
}

static void	split_cmd_argument(
							void *const input_params,
							t_arg_parser *arg_parser,
							t_cmd_param_type cmd_param_type)
{
	t_input_param_save		fn_input_param_save;
	t_argc_argv				*argc_argv;
	const char				*arg;

	argc_argv = &arg_parser->argc_argv;
	fn_input_param_save = arg_parser->fn_input_param_save;
	arg = (*argc_argv->argv)[argc_argv->i];
	if (cmd_param_type == E_OPTIONAL_SHORT)
	{
		while (*(++arg))
		{
			if (!pre_analyse_argument(arg_parser->options, *arg, argc_argv))
				cmd_param_type = E_MANDATORY;
			fn_input_param_save(input_params, *arg, argc_argv, cmd_param_type);
			if (cmd_param_type == E_MANDATORY)
				break ;
		}
	}
	else if (cmd_param_type == E_MANDATORY || cmd_param_type == E_OPTIONAL_LONG)
		fn_input_param_save(input_params, *arg, argc_argv, cmd_param_type);
	return ;
}

const void	*ft_arg_parser(t_arg_parser *arg_parser)
{
	t_cmd_param_type		cmd_param_type;
	t_argc_argv				*argc_argv;
	const char				*arg;
	void					*input_params;

	argc_argv = &arg_parser->argc_argv;
	input_params = (void *)arg_parser->fn_input_params_initialize(argc_argv);
	while (++argc_argv->i < *argc_argv->argc)
	{
		arg = (*argc_argv->argv)[argc_argv->i];
		if (ft_strlen(arg) > 2 && arg[0] == '-' && arg[1] == '-')
			cmd_param_type = E_OPTIONAL_LONG;
		else if (ft_strlen(arg) > 1 && arg[0] == '-')
			cmd_param_type = E_OPTIONAL_SHORT;
		else
			cmd_param_type = E_MANDATORY;
		split_cmd_argument(input_params, arg_parser, cmd_param_type);
	}
	return (input_params);
}
