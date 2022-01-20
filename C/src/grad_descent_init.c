/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grad_descent_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:15:53 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/20 12:42:53 by jkauppi          ###   ########.fr       */
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
				input_data->num_of_input_functions);
		num_of_layers = grad_descent_attr->hyper_params->num_of_layers;
		grad_descent_attr->neural_network
			= neural_network_init(input_data->dataset_array,
				grad_descent_attr->hyper_params);
		grad_descent_attr->dataset = input_data->dataset_array[E_TRAIN];
		layer = grad_descent_attr->neural_network->layers[num_of_layers - 1];
		i.rows = layer->num_of_nodes;
		i.cols = layer->y_hat_train->size.cols;
	}
	else
		grad_descent_attr = NULL;
	return (grad_descent_attr);
}
