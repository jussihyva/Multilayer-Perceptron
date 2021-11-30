/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grad_descent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhani <juhani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 09:12:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/30 15:56:18 by juhani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	weight_bias_update(
						const t_layer *const layer,
						const double learning_rate)
{
	size_t		i;
	size_t		total_size;

	total_size = layer->weight->size.rows * layer->weight->size.cols;
	i = -1;
	while (++i < total_size)
		((double *)layer->weight->data)[i] -= learning_rate
			* ((double *)layer->d_weight->data)[i];
	total_size = layer->bias->size;
	i = -1;
	while (++i < total_size)
		((double *)layer->bias->data)[i] -= learning_rate
			* ((double *)layer->d_bias->data)[i];
	return ;
}

static void	calculate_derivatives(
							const t_layer *const layer,
							const t_dataset *const dataset)
{
	calculate_derivative_z(layer->a_output, dataset->y, layer->d_z);
	calculate_derivative_w(dataset->x, layer->d_z, layer->d_weight);
	calculate_derivative_b(layer->d_z, layer->d_bias);
	return ;
}

t_grad_descent_attr	*grad_descent_attr_initialize(
									const char *const dataset_file,
									const char *const weight_bias_file,
									const t_hyper_params *const hyper_params)
{
	t_grad_descent_attr		*grad_descent_attr;
	const t_layer			*layer;
	t_dataset				*dataset;

	dataset = dataset_init(dataset_file);
	if (dataset)
	{
		grad_descent_attr = ft_memalloc(sizeof(*grad_descent_attr));
		grad_descent_attr->logistic_reg_attr = logistic_reg_init(dataset);
		grad_descent_attr->dataset = dataset;
		grad_descent_attr->hyper_params = hyper_params;
		grad_descent_attr->weight_bias_file = weight_bias_file;
		layer = grad_descent_attr->logistic_reg_attr->neural_network
			->layers[NUM_OF_LAYERS - 1];
		grad_descent_attr->cost = ml_vector_create(layer->num_of_nodes);
		grad_descent_attr->softmax = ml_matrix_create(layer->a_output->size.rows,
				layer->a_output->size.cols);
		grad_descent_attr->argmax
			= ml_vector_create(grad_descent_attr->softmax->size.cols);
		grad_descent_attr->argmax_values
			= ml_vector_create(grad_descent_attr->softmax->size.cols);
	}
	else
		grad_descent_attr = NULL;
	return (grad_descent_attr);
}

const t_vector	*grad_descent(
				const t_layer *const *const layers,
				const t_dataset *const dataset,
				const t_hyper_params *const hyper_params,
				const t_tcp_connection *const influxdb_connection)
{
	const t_layer		*layer;
	size_t				i;
	size_t				iter_cnt;
	t_vector			*cost;

	layer = layers[NUM_OF_LAYERS - 1];
	cost = ml_vector_create(layer->num_of_nodes);
	iter_cnt = -1;
	while (++iter_cnt < hyper_params->epochs)
	{
		i = 0;
		while (++i < NUM_OF_LAYERS)
			logistic_regression(layers[i]);
		layer = layers[NUM_OF_LAYERS - 1];
		ml_matrix_cost(dataset->y, layer->a_output, cost);
		i = NUM_OF_LAYERS;
		while (--i)
		{
			calculate_derivatives(layers[i], dataset);
			weight_bias_update(layer, hyper_params->learning_rate);
		}
		send_iteration_result_to_database(influxdb_connection, cost, iter_cnt);
	}
	return (cost);
}

void	grad_descent_attr_remove(
						t_grad_descent_attr **grad_descent_attr)
{
	if (*grad_descent_attr)
	{
		logistic_reg_attr_remove(&(*grad_descent_attr)->logistic_reg_attr);
		dataset_remove(&(*grad_descent_attr)->dataset);
		ml_vector_remove((t_vector **)&(*grad_descent_attr)->cost);
		ml_matrix_remove(&(*grad_descent_attr)->softmax);
		ml_vector_remove((t_vector **)&(*grad_descent_attr)->argmax);
		ml_vector_remove((t_vector **)&(*grad_descent_attr)->argmax_values);
		if ((*grad_descent_attr)->influxdb_connection)
			ft_influxdb_remove(&(*grad_descent_attr)->influxdb_connection);
		ft_memdel((void **)grad_descent_attr);
	}
	return ;
}
