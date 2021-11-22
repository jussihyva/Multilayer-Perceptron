/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prediction_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:44:14 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/22 11:02:31 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

t_prediction	*prediction_init(const int argc, const char *const *const argv)
{
	t_prediction	*prediction;

	prediction = ft_memalloc(sizeof(*prediction));
	prediction->argc_argv.argc = argc;
	prediction->argc_argv.argv = argv;
	prediction->arg_parser = ft_arg_parser_init(&prediction->argc_argv,
			arg_init, arg_analyze, arg_usage_prediction);
	prediction->cmd_args = ft_arg_parser(prediction->arg_parser);
	prediction->grad_descent_attr
		= grad_descent_attr_initialize(prediction->cmd_args->dataset_file,
			prediction->cmd_args->weight_bias_file);
	return (prediction);
}
