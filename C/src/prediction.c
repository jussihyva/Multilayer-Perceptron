/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prediction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:14:47 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/22 14:51:15 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	arg_parser_remove(t_arg_parser **arg_parser)
{
	ft_strdel((char **)&(*arg_parser)->options);
	ft_memdel((void **)arg_parser);
	return ;
}

static void	main_remove(t_prediction **prediction, const char *const prog_name)
{
	t_bool					print_leaks;
	const t_cmd_args		*cmd_args;
	t_grad_descent_attr		*grad_descent_attr;
	t_arg_parser			*arg_parser;

	cmd_args = (*prediction)->cmd_args;
	grad_descent_attr = (*prediction)->grad_descent_attr;
	arg_parser = (*prediction)->arg_parser;
	print_leaks = cmd_args->print_leaks;
	grad_descent_attr_remove(&grad_descent_attr);
	arg_remove(&cmd_args);
	arg_parser_remove(&arg_parser);
	ft_memdel((void **)prediction);
	if (print_leaks)
		ft_print_leaks(prog_name);
	return ;
}

static void	print_result(
				const t_matrix *const y_hat,
				const t_matrix *const y,
				const t_matrix *const softmax,
				const t_vector *const argmax_values)
{
	ml_matrix_print("Prediction", y_hat);
	ml_matrix_print("Observed", y);
	ml_matrix_print("Softmax", softmax);
	ml_vector_print("ARGMAX VALUES", argmax_values);
	return ;
}

int	main(int argc, char **argv)
{
	t_prediction			*prediction;
	t_grad_descent_attr		*grad_descent_attr;
	const t_layer			*layer;

	prediction = prediction_init(argc, (const char *const *)argv);
	grad_descent_attr = prediction->grad_descent_attr;
	if (grad_descent_attr)
	{
		layer = &grad_descent_attr->logistic_reg_attr->neural_network
			->layers[0];
		grad_descent_attr->influxdb_connection
			= ft_influxdb_connect("127.0.0.1", "8086", E_TLS);
		bias_weigth_values_set(layer->bias, layer->weight,
			prediction->cmd_args->weight_bias_file);
		logistic_regression(layer);
		grad_descent_attr->softmax = ml_matrix_create(layer->y_hat->size.rows,
				layer->y_hat->size.cols);
		ml_softmax(layer->y_hat, grad_descent_attr->softmax);
		send_softmax_result_to_database(grad_descent_attr);
		grad_descent_attr->argmax
			= ml_vector_create(grad_descent_attr->softmax->size.cols);
		grad_descent_attr->argmax_values
			= ml_vector_create(grad_descent_attr->softmax->size.cols);
		ml_argmax(grad_descent_attr->softmax, grad_descent_attr->argmax,
			grad_descent_attr->argmax_values);
		if (ft_logging_level() <= LOG_INFO)
			print_result(layer->y_hat, grad_descent_attr->dataset->y,
				grad_descent_attr->softmax, grad_descent_attr->argmax_values);
	}
	main_remove(&prediction, "prediction");
	return (0);
}
