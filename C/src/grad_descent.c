/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grad_descent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 09:12:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/17 12:57:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

t_grad_descent_attr	*grad_descent_attr_initialize(
									const t_input_data *const input_data,
									const char *const weight_bias_file,
									const t_hyper_params *const hyper_params)
{
	t_grad_descent_attr		*grad_descent_attr;
	const t_layer_output	*layer;

	if (input_data->dataset_array[E_TRAIN])
	{
		grad_descent_attr = ft_memalloc(sizeof(*grad_descent_attr));
		grad_descent_attr->neural_network
			= neural_network_init((const t_dataset *const *)
				input_data->dataset_array, hyper_params);
		grad_descent_attr->dataset = input_data->dataset_array[E_TRAIN];
		grad_descent_attr->hyper_params = hyper_params;
		grad_descent_attr->weight_bias_file = weight_bias_file;
		layer = grad_descent_attr->neural_network->layers[OUTPUT_LAYER_ID];
		grad_descent_attr->softmax = ml_matrix_create(
				layer->num_of_nodes, layer->y_hat_train->size.cols);
		grad_descent_attr->argmax
			= ml_vector_create(grad_descent_attr->softmax->size.cols);
		grad_descent_attr->argmax_values
			= ml_vector_create(grad_descent_attr->softmax->size.cols);
	}
	else
		grad_descent_attr = NULL;
	return (grad_descent_attr);
}

void	grad_descent(
				const t_neural_network *const neural_network,
				const t_hyper_params *const hyper_params,
				const t_tcp_connection *const influxdb_connection)
{
	void *const		*layers;
	t_layer_output	*layer_output;	
	size_t			iter_cnt;

	layers = neural_network->layers;
	iter_cnt = 0;
	while (++iter_cnt <= hyper_params->epochs)
	{
		neural_network_mode_set(layers, neural_network->layer_types, E_TRAIN);
		propagation_forward(layers, neural_network->layer_types);
		propagation_backward(layers, neural_network->layer_types);
		send_iteration_result_to_database(influxdb_connection, layers,
			iter_cnt);
		neural_network_mode_set(layers, neural_network->layer_types, E_TEST);
		propagation_forward(layers, neural_network->layer_types);
		if (!(iter_cnt % 100) || iter_cnt == hyper_params->epochs)
		{
			layer_output = ((t_layer_output **)layers)[OUTPUT_LAYER_ID];
			ft_printf("epoch %lu/%lu - loss: %f", iter_cnt,
				hyper_params->epochs,
				((double *)layer_output->cost[E_TRAIN]->data)[0]);
			ft_printf(" - val_loss: %f\n",
				((double *)layer_output->cost[E_TEST]->data)[0]);
		}
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
		neural_network_remove(&(*grad_descent_attr)->neural_network);
		ft_memdel((void **)grad_descent_attr);
	}
	return ;
}
