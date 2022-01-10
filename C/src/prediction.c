/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prediction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:14:47 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/11 00:01:10 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	arg_parser_remove(t_arg_parser **arg_parser)
{
	ft_strdel((char **)&(*arg_parser)->argc_argv->opt_pars);
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
	input_data_remove(&(*prediction)->input_data);
	arg_remove(&cmd_args);
	arg_parser_remove(&arg_parser);
	ft_memdel((void **)prediction);
	if (print_leaks)
		ft_print_leaks(prog_name);
	return ;
}

static void	print_result(t_grad_descent_attr *grad_descent_attr)
{
	ml_matrix_print("Observed", grad_descent_attr->dataset->y);
	ml_matrix_print("Softmax", grad_descent_attr->softmax);
	ml_vector_print("ARGMAX VALUES", grad_descent_attr->argmax_values);
	return ;
}

int	main(int argc, char **argv)
{
	t_prediction				*prediction;
	t_grad_descent_attr			*grad_descent_attr;
	const t_neural_network		*neural_network;
	size_t						num_of_layers;

	prediction = prediction_init(argc, (const char *const *)argv);
	grad_descent_attr = prediction->grad_descent_attr;
	if (grad_descent_attr)
	{
		num_of_layers = grad_descent_attr->hyper_params->num_of_layers;
		neural_network = grad_descent_attr->neural_network;
		propagation_forward(neural_network->layers,
			neural_network->layer_types, num_of_layers);
		ml_softmax(((t_layer_output *)neural_network->layers[num_of_layers - 1])
			->y_hat, grad_descent_attr->softmax);
		if (grad_descent_attr->influxdb_connection)
			send_softmax_result_to_database(grad_descent_attr
				->influxdb_connection, grad_descent_attr->softmax);
		else
			FT_LOG_DEBUG("Softmax values are not sent to influxdb");
		ml_argmax(grad_descent_attr->softmax, grad_descent_attr->argmax,
			grad_descent_attr->argmax_values);
		if (ft_logging_level() <= LOG_INFO)
			print_result(grad_descent_attr);
		prediction_validate(grad_descent_attr->dataset->y,
			grad_descent_attr->argmax);
	}
	main_remove(&prediction, "prediction");
	return (0);
}
