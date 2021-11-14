/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grad_descent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 09:12:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/14 09:50:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

t_grad_descent_attr	*grad_descent_attr_initialize(void)
{
	t_grad_descent_attr		*grad_descent_attr;
	t_layer					*layer;

	grad_descent_attr = ft_memalloc(sizeof(*grad_descent_attr));
	grad_descent_attr->logistic_reg_attr
		= ft_memalloc(sizeof(*grad_descent_attr->logistic_reg_attr));
	grad_descent_attr->dataset = read_dataset("../Data/data.csv");
	grad_descent_attr->logistic_reg_attr->neural_network
		= neural_network_initialize(grad_descent_attr->dataset);
	layer = &grad_descent_attr->logistic_reg_attr->neural_network->layers[0];
	grad_descent_attr->cost = ml_vector_create(layer->num_of_nodes);
	return (grad_descent_attr);
}

void	grad_descent(t_grad_descent_attr *grad_descent_attr)
{
	t_layer					*layer;

	layer = &grad_descent_attr->logistic_reg_attr->neural_network->layers[0];
	logistic_regression(grad_descent_attr, layer);
	return ;
}

void	grad_descent_attr_remove(
						t_grad_descent_attr **grad_descent_attr)
{
	logistic_reg_attr_remove(&(*grad_descent_attr)->logistic_reg_attr);
	dataset_remove(&(*grad_descent_attr)->dataset);
	ml_vector_remove(&(*grad_descent_attr)->cost);
	ft_memdel((void **)grad_descent_attr);
	return ;
}
