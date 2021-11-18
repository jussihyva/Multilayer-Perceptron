/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logistic_regression.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 11:55:45 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/18 12:52:01 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	logistic_regression(const t_layer *const layer)
{
	linear_function(layer);
	ml_sigmoid(layer->z, layer->y_hat);
	return ;
}

void	logistic_reg_attr_remove(
						t_logistic_reg_attr **logistic_reg_attr)
{
	t_layer				*layer;
	t_neural_network	*neural_network;

	neural_network = (*logistic_reg_attr)->neural_network;
	layer = &neural_network->layers[0];
	ml_matrix_remove(&layer->z);
	ml_matrix_remove(&layer->y_hat);
	ml_matrix_remove(&layer->weight);
	ml_vector_remove(&layer->bias);
	ml_vector_remove(&layer->derivative_b);
	ml_matrix_remove(&layer->derivative_w);
	ml_matrix_remove(&layer->derivative_z);
	ft_memdel((void **)&neural_network->layers);
	ft_memdel((void **)&(*logistic_reg_attr)->neural_network);
	ft_memdel((void **)logistic_reg_attr);
	return ;
}
