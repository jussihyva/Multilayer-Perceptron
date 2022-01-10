/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:53:50 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/10 17:55:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	set_mode_for_input(t_layer_input *const layer,
					const t_dataset_type dataset_type)
{
	layer->dataset_type = dataset_type;
	if (dataset_type == E_TRAIN)
	{
		layer->x = layer->x_train;
		layer->a = layer->a_train;
	}
	else
	{
		layer->x = layer->x_test;
		layer->a = layer->a_test;
	}
	return ;
}

static void	set_mode_for_hidden(t_layer_hidden *const layer,
					const t_dataset_type dataset_type)
{
	layer->dataset_type = dataset_type;
	if (dataset_type == E_TRAIN)
	{
		layer->z = layer->z_train;
		layer->a = layer->a_train;
	}
	else
	{
		layer->z = layer->z_test;
		layer->a = layer->a_test;
	}
	return ;
}

static void	set_mode_for_output(t_layer_output *const layer,
					const t_dataset_type dataset_type)
{
	layer->dataset_type = dataset_type;
	if (dataset_type == E_TRAIN)
	{
		layer->z = layer->z_train;
		layer->y = layer->y_train;
		layer->y_hat = layer->y_hat_train;
	}
	else
	{
		layer->z = layer->z_test;
		layer->y = layer->y_test;
		layer->y_hat = layer->y_hat_test;
	}
	return ;
}

void	layer_mode_set(
				const t_neural_network *const neural_network,
				const t_dataset_type dataset_type,
				const size_t num_of_layers)
{
	void *const			*layers;
	const t_layer_type	*layer_types;
	size_t				i;

	layers = neural_network->layers;
	layer_types = neural_network->layer_types;
	i = -1;
	while (++i < num_of_layers)
	{
		if (layer_types[i] == E_LAYER_INPUT)
			set_mode_for_input(layers[i], dataset_type);
		else if (layer_types[i] == E_LAYER_OUTPUT)
			set_mode_for_output(layers[i], dataset_type);
		else
			set_mode_for_hidden(layers[i], dataset_type);
	}
	return ;
}
