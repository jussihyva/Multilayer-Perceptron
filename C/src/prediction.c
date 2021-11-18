/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prediction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:14:47 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/18 13:58:32 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	arg_parser_remove(t_arg_parser **arg_parser)
{
	ft_strdel((char **)&(*arg_parser)->options);
	ft_memdel((void **)arg_parser);
	return ;
}

static void	main_remove(
					t_arg_parser **arg_parser,
					const t_cmd_args **const cmd_args,
					t_grad_descent_attr **grad_descent_attr)
{
	t_bool			print_leaks;

	print_leaks = (*cmd_args)->print_leaks;
	grad_descent_attr_remove(grad_descent_attr);
	arg_remove(cmd_args);
	arg_parser_remove(arg_parser);
	if (print_leaks)
		ft_print_leaks("training");
	return ;
}

int	main(int argc, char **argv)
{
	t_grad_descent_attr		*grad_descent_attr;
	t_arg_parser			*arg_parser;
	t_argc_argv				argc_argv;
	const t_cmd_args		*cmd_args;
	const t_layer			*layer;

	argc_argv.argc = (const int *)&argc;
	argc_argv.argv = (const char ***)&argv;
	arg_parser = ft_arg_parser_init(&argc_argv, arg_init, arg_analyze,
			arg_usage_prediction);
	cmd_args = ft_arg_parser(arg_parser);
	grad_descent_attr = grad_descent_attr_initialize(cmd_args->dataset_file,
			cmd_args->weight_bias_file);
	if (grad_descent_attr)
	{
		grad_descent_attr->influxdb_connection
			= ft_influxdb_connect("127.0.0.1", "8086", E_TLS);
		layer = &grad_descent_attr->logistic_reg_attr->neural_network
			->layers[0];
		bias_weigth_values_set(layer->bias, layer->weight,
			cmd_args->weight_bias_file);
		logistic_regression(layer);
		if (ft_logging_level() <= LOG_INFO)
		{
			ml_matrix_print("Prediction", layer->y_hat);
			ml_matrix_print("Observed", grad_descent_attr->dataset->y);
		}
	}
	main_remove(&arg_parser, &cmd_args, &grad_descent_attr);
	return (0);
}
