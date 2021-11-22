/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:46:28 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/22 11:07:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	*arg_init(t_argc_argv *argc_argv)
{
	t_cmd_args		*cmd_args;
	const char		*program_folder;

	cmd_args = ft_memalloc(sizeof(*cmd_args));
	cmd_args->argc_argv = argc_argv;
	cmd_args->logging_level = LOG_WARN;
	cmd_args->logging_data = ft_event_logging_init(DEFAULT_LOGGING_LEVEL);
	cmd_args->hyper_parameters.iterations = ITERATION_LOOP;
	cmd_args->hyper_parameters.learning_rate = LEARNING_RATE;
	program_folder = dirname(((char **)argc_argv->argv)[0]);
	cmd_args->weight_bias_file = ft_strjoin(program_folder, BIAS_WEIGTH_FILE);
	ft_strdel((char **)&program_folder);
	return (cmd_args);
}
