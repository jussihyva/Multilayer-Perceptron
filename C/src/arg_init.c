/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:46:28 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/16 18:58:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	*arg_init(t_argc_argv *argc_argv)
{
	t_cmd_args		*cmd_args;

	cmd_args = ft_memalloc(sizeof(*cmd_args));
	cmd_args->argc_argv = argc_argv;
	cmd_args->logging_level = LOG_WARN;
	cmd_args->logging_data = ft_event_logging_init(DEFAULT_LOGGING_LEVEL);
	cmd_args->hyper_parameters.iterations = ITERATION_LOOP;
	cmd_args->hyper_parameters.learning_rate = LEARNING_RATE;
	return (cmd_args);
}
