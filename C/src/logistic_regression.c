/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logistic_regression.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 11:55:45 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/13 19:42:59 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	logistic_regression(
				const t_grad_descent_attributes *const grad_descent_attributes,
				t_logistic_reg_attributes *const logistic_reg_attributes)
{
	t_layer		*layer;

	layer = &logistic_reg_attributes->neural_network->layers[0];
	linear_function(layer);
	ml_sigmoid(layer->z, layer->y_hat);
	ml_matrix_cost(grad_descent_attributes->dataset->y, layer->y_hat,
		logistic_reg_attributes->cost);
	ml_vector_print("Cost", logistic_reg_attributes->cost);
	layer->derivative_z = calculate_derivative_z(layer->y_hat,
			grad_descent_attributes->dataset->y);
	ml_vector_print("dz", layer->derivative_z);
	layer->derivative_w
		= calculate_derivative_w(grad_descent_attributes->dataset->x,
			layer->derivative_z);
	layer->derivative_b
		= calculate_derivative_b(layer->derivative_z);
	ml_matrix_print("dw", layer->derivative_w);
	ml_vector_print("db", layer->derivative_b);
	return ;
}

void	logistic_reg_attributes_remove(
						t_logistic_reg_attributes **logistic_reg_attributes)
{
	t_layer				*layer;
	t_neural_network	*neural_network;

	neural_network = (*logistic_reg_attributes)->neural_network;
	layer = &neural_network->layers[0];
	ml_matrix_remove(&layer->z);
	ml_matrix_remove(&layer->y_hat);
	ml_matrix_remove(&layer->weight);
	ml_vector_remove(&layer->bias);
	ml_vector_remove(&layer->derivative_b);
	ml_matrix_remove(&layer->derivative_w);
	ml_vector_remove(&layer->derivative_z);
	ml_vector_remove(&(*logistic_reg_attributes)->cost);
	ft_memdel((void **)&neural_network->layers);
	ft_memdel((void **)&(*logistic_reg_attributes)->neural_network);
	ft_memdel((void **)logistic_reg_attributes);
	return ;
}
