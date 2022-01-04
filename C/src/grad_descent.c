/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grad_descent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 09:12:46 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/04 13:07:48 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

t_grad_descent_attr	*grad_descent_attr_initialize(
								const t_input_data *const input_data,
								const char *const weight_bias_file,
								const t_hyper_params *const input_hyper_params)
{
	t_grad_descent_attr		*grad_descent_attr;
	const t_layer_output	*layer;
	t_size_2d				i;
	size_t					num_of_layers;

	if (input_data->dataset_array[E_TRAIN])
	{
		grad_descent_attr = ft_memalloc(sizeof(*grad_descent_attr));
		grad_descent_attr->weight_bias_file = weight_bias_file;
		grad_descent_attr->hyper_params
			= hyper_params_init(weight_bias_file, input_hyper_params,
				input_data->num_of_input_functions,
				input_data->num_of_output_functions);
		num_of_layers = grad_descent_attr->hyper_params->num_of_layers;
		grad_descent_attr->neural_network
			= neural_network_init((const t_dataset *const *)
				input_data->dataset_array, grad_descent_attr->hyper_params);
		grad_descent_attr->dataset = input_data->dataset_array[E_TRAIN];
		layer = grad_descent_attr->neural_network->layers[num_of_layers - 1];
		i.rows = layer->num_of_nodes;
		i.cols = layer->y_hat_train->size.cols;
		grad_descent_attr->softmax = ml_matrix_create(i);
		i.rows = grad_descent_attr->softmax->size.cols;
		grad_descent_attr->argmax = ml_vector_create(i.rows);
		grad_descent_attr->argmax_values = ml_vector_create(i.rows);
	}
	else
		grad_descent_attr = NULL;
	return (grad_descent_attr);
}

static void	cost_values_print(
					const size_t iter_cnt,
					const size_t epochs,
					t_vector *cost[2])
{
	ft_printf("epoch %lu/%lu - loss: %f", iter_cnt, epochs,
		((double *)cost[E_TRAIN]->data)[0]);
	ft_printf(" - val_loss: %f\n", ((double *)cost[E_TEST]->data)[0]);
	return ;
}

void	grad_descent(
				const t_neural_network *const neural_network,
				const t_hyper_params *const hyper_params,
				const t_tcp_connection *const influxdb_connection)
{
	void *const		*layers;
	t_layer_output	*layer_output;	
	size_t			iter_cnt;
	size_t			num_of_layers;

	num_of_layers = hyper_params->num_of_layers;
	layers = neural_network->layers;
	layer_output = ((t_layer_output **)layers)[num_of_layers - 1];
	iter_cnt = 0;
	while (++iter_cnt <= hyper_params->epochs)
	{
		neural_network_mode_set(layers, neural_network->layer_types, E_TRAIN,
			num_of_layers);
		propagation_forward(layers, neural_network->layer_types, num_of_layers);
		propagation_backward(layers, neural_network->layer_types,
			num_of_layers);
		send_iteration_result_to_database(influxdb_connection, layer_output,
			iter_cnt);
		send_hyper_params_to_database(influxdb_connection, hyper_params);
		neural_network_mode_set(layers, neural_network->layer_types, E_TEST,
			num_of_layers);
		propagation_forward(layers, neural_network->layer_types, num_of_layers);
		if (!(iter_cnt % 100) || iter_cnt == hyper_params->epochs)
			cost_values_print(iter_cnt, hyper_params->epochs,
				layer_output->cost);
	}
	return ;
}

void	grad_descent_attr_remove(
						t_grad_descent_attr **grad_descent_attr)
{
	if (*grad_descent_attr)
	{
		ml_matrix_remove((t_matrix **)&(*grad_descent_attr)->softmax);
		ml_vector_remove((t_vector **)&(*grad_descent_attr)->argmax);
		ml_vector_remove((t_vector **)&(*grad_descent_attr)->argmax_values);
		if ((*grad_descent_attr)->influxdb_connection)
			ft_influxdb_remove(&(*grad_descent_attr)->influxdb_connection);
		neural_network_remove(&(*grad_descent_attr)->neural_network,
			(*grad_descent_attr)->hyper_params->num_of_layers);
		ft_memdel((void **)grad_descent_attr);
	}
	return ;
}
