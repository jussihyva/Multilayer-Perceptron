/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:23:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/13 19:24:00 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// while [ condition ]; do time ./training ; done

#include "multilayer_perceptron.h"

int	main(void)
{
	t_grad_descent_attributes	grad_descent_attributes;
	t_logistic_reg_attributes	*logistic_reg_attributes;
	t_layer						*layer;

	logistic_reg_attributes = ft_memalloc(sizeof(*logistic_reg_attributes));
	grad_descent_attributes.dataset = read_dataset("../Data/data.csv");
	logistic_reg_attributes->neural_network
		= neural_network_initialize(grad_descent_attributes.dataset);
	layer = &logistic_reg_attributes->neural_network->layers[0];
	logistic_reg_attributes->cost = ml_vector_create(layer->num_of_nodes);
	logistic_regression(&grad_descent_attributes, logistic_reg_attributes);
	dataset_remove(&grad_descent_attributes.dataset);
	logistic_reg_attributes_remove(&logistic_reg_attributes);
	return (0);
}
