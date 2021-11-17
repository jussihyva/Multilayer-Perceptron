/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grad_descent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 09:12:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/17 12:33:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	weight_bias_update(t_layer *const layer, const double learning_rate)
{
	size_t		i;
	size_t		total_size;

	total_size = layer->weight->size.rows * layer->weight->size.cols;
	i = -1;
	while (++i < total_size)
		((double *)layer->weight->data)[i] -= learning_rate
			* ((double *)layer->derivative_w->data)[i];
	total_size = layer->bias->size;
	i = -1;
	while (++i < total_size)
		((double *)layer->bias->data)[i] -= learning_rate
			* ((double *)layer->derivative_b->data)[i];
	return ;
}

static void	calculate_derivatives(
							t_layer *const layer,
							t_dataset *dataset)
{
	calculate_derivative_z(layer->y_hat, dataset->y, layer->derivative_z);
	ml_matrix_print("dz", layer->derivative_z);
	calculate_derivative_w(dataset->x, layer->derivative_z,
		layer->derivative_w);
	calculate_derivative_b(layer->derivative_z, layer->derivative_b);
	ml_matrix_print("dw", layer->derivative_w);
	ml_vector_print("db", layer->derivative_b);
	return ;
}

t_grad_descent_attr	*grad_descent_attr_initialize(
										const char *const dataset_file)
{
	t_grad_descent_attr		*grad_descent_attr;
	t_layer					*layer;
	t_dataset				*dataset;

	dataset = read_dataset(dataset_file);
	if (dataset)
	{
		grad_descent_attr = ft_memalloc(sizeof(*grad_descent_attr));
		grad_descent_attr->logistic_reg_attr
			= ft_memalloc(sizeof(*grad_descent_attr->logistic_reg_attr));
		grad_descent_attr->dataset = dataset;
		grad_descent_attr->logistic_reg_attr->neural_network
			= neural_network_initialize(grad_descent_attr->dataset);
		grad_descent_attr->hyper_params
			= ft_memalloc(sizeof(*grad_descent_attr->hyper_params));
		grad_descent_attr->hyper_params->iters = 100;
		grad_descent_attr->hyper_params->learning_rate = 0.2;
		layer = &grad_descent_attr->logistic_reg_attr
			->neural_network->layers[0];
		grad_descent_attr->cost = ml_vector_create(layer->num_of_nodes);
	}
	else
		grad_descent_attr = NULL;
	return (grad_descent_attr);
}

void	grad_descent(t_grad_descent_attr *grad_descent_attr)
{
	t_layer			*layer;
	t_dataset		*dataset;
	size_t			i;

	layer = &grad_descent_attr->logistic_reg_attr->neural_network->layers[0];
	dataset = grad_descent_attr->dataset;
	i = -1;
	while (++i < grad_descent_attr->hyper_params->iters)
	{
		logistic_regression(layer);
		ml_matrix_cost(dataset->y, layer->y_hat, grad_descent_attr->cost);
		ml_vector_print("Cost", grad_descent_attr->cost);
		calculate_derivatives(layer, dataset);
		weight_bias_update(layer,
			grad_descent_attr->hyper_params->learning_rate);
		send_iteration_result_to_database(grad_descent_attr);
	}
	return ;
}

void	grad_descent_attr_remove(
						t_grad_descent_attr **grad_descent_attr)
{
	if (*grad_descent_attr)
	{
		logistic_reg_attr_remove(&(*grad_descent_attr)->logistic_reg_attr);
		dataset_remove(&(*grad_descent_attr)->dataset);
		ml_vector_remove(&(*grad_descent_attr)->cost);
		ft_memdel((void **)&(*grad_descent_attr)->hyper_params);
		if ((*grad_descent_attr)->influxdb_connection)
			ft_influxdb_remove(&(*grad_descent_attr)->influxdb_connection);
		ft_memdel((void **)grad_descent_attr);
	}
	return ;
}
