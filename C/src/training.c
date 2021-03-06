/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:23:11 by jkauppi           #+#    #+#             */
/*   Updated: 2022/07/03 14:35:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// while [ condition ]; do time ./training ; done

#include "multilayer_perceptron.h"

static void	arg_parser_remove(t_arg_parser **arg_parser)
{
	ft_strdel((char **)&(*arg_parser)->argc_argv->opt_pars);
	ft_memdel((void **)arg_parser);
	return ;
}

static void	main_remove(t_training **training, const char *const prog_name)
{
	t_bool					print_leaks;
	const t_cmd_args		*cmd_args;
	t_grad_descent_attr		*grad_descent_attr;
	t_arg_parser			*arg_parser;

	cmd_args = (*training)->cmd_args;
	grad_descent_attr = (*training)->grad_descent_attr;
	arg_parser = (*training)->arg_parser;
	print_leaks = cmd_args->print_leaks;
	grad_descent_attr_remove(&grad_descent_attr);
	input_data_remove(&(*training)->input_data);
	arg_remove(&cmd_args);
	arg_parser_remove(&arg_parser);
	ft_memdel((void **)training);
	if (print_leaks)
		ft_print_leaks(prog_name);
	return ;
}

int	main(int argc, char **argv)
{
	t_training					*training;
	t_grad_descent_attr			*grad_descent_attr;
	const t_neural_network		*neural_network;
	void *const					*layers;
	size_t						iter_cnt;

	training = training_init(argc, (const char *const *)argv);
	grad_descent_attr = training->grad_descent_attr;
	if (grad_descent_attr)
	{
		neural_network = grad_descent_attr->neural_network;
		layers = neural_network->layers;
		iter_cnt = grad_descent(neural_network, grad_descent_attr->hyper_params,
				grad_descent_attr->influxdb_connection);
		cost_values_print(iter_cnt, grad_descent_attr->hyper_params->epochs,
			layers[grad_descent_attr->hyper_params->num_of_layers - 1]);
		neural_network_save(layers, neural_network->layer_types,
			grad_descent_attr->weight_bias_file,
			grad_descent_attr->hyper_params);
	}
	main_remove(&training, "training");
	return (0);
}
