/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grad_descent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 09:12:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/14 12:50:45 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

t_grad_descent_attr	*grad_descent_attr_initialize(
									const char *const dataset_file,
									const char *const weight_bias_file,
									const t_hyper_params *const hyper_params)
{
	t_grad_descent_attr				*grad_descent_attr;
	const t_layer_output			*layer;
	t_dataset						*dataset_train;
	t_dataset						*dataset_test;
	t_file_attr						*file_attr;
	t_neural_network_input_data		*neural_network_input_data;

	dataset_train = ft_memalloc(sizeof(*dataset_train));
	dataset_test = ft_memalloc(sizeof(*dataset_test));
	file_attr = ft_read_file(dataset_file, E_CSV);
	grad_descent_attr = NULL;
	if (!file_attr || file_attr->read_failure)
		FT_LOG_ERROR("Reading of file %s failed!", dataset_file);
	else
	{
		neural_network_input_data = dataset_split_input_data_for_train_and_test(
				file_attr->row_array, file_attr->rows, dataset_train, dataset_test);
		if (dataset_train)
		{
			grad_descent_attr = ft_memalloc(sizeof(*grad_descent_attr));
			grad_descent_attr->neural_network = neural_network_init(dataset_train,
					hyper_params);
			grad_descent_attr->dataset = dataset_train;
			grad_descent_attr->hyper_params = hyper_params;
			grad_descent_attr->weight_bias_file = weight_bias_file;
			layer = grad_descent_attr->neural_network->layers[OUTPUT_LAYER_ID];
			grad_descent_attr->softmax = ml_matrix_create(
					layer->y_hat->size.rows, layer->y_hat->size.cols);
			grad_descent_attr->argmax
				= ml_vector_create(grad_descent_attr->softmax->size.cols);
			grad_descent_attr->argmax_values
				= ml_vector_create(grad_descent_attr->softmax->size.cols);
		}
		else
			grad_descent_attr = NULL;
	}
	return (grad_descent_attr);
}

void	grad_descent(
				const t_neural_network *const neural_network,
				const t_hyper_params *const hyper_params,
				const t_tcp_connection *const influxdb_connection)
{
	const void *const	*layers;
	size_t				iter_cnt;

	layers = neural_network->layers;
	iter_cnt = 0;
	while (++iter_cnt <= hyper_params->epochs)
	{
		propagation_forward(neural_network->layers, neural_network->layer_types,
			hyper_params->epochs, iter_cnt);
		propagation_backward(neural_network->layers, neural_network->layer_types,
			hyper_params->epochs, iter_cnt);
		send_iteration_result_to_database(influxdb_connection, layers,
			iter_cnt);
	}
	return ;
}

void	grad_descent_attr_remove(
						t_grad_descent_attr **grad_descent_attr)
{
	if (*grad_descent_attr)
	{
		dataset_remove(&(*grad_descent_attr)->dataset);
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
