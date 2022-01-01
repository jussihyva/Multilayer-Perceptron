/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neural_network.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:15:53 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/01 21:26:37 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	**layers_init(
							const t_layer_type *const layer_types,
							const t_dataset *const *const dataset_array,
							const t_hyper_params *const hyper_params)
{
	size_t		i;
	void		**layers;

	layers = ft_memalloc(sizeof(*layers) * hyper_params->num_of_layers);
	i = -1;
	while (++i < hyper_params->num_of_layers)
		layers[i] = layer_init(i, layer_types[i], dataset_array, hyper_params);
	return (layers);
}

static const t_layer_type	*layer_types_init(const size_t num_of_layers)
{
	size_t				layer_id;
	t_layer_type		*layer_types;

	layer_types = ft_memalloc(sizeof(*layer_types) * num_of_layers);
	layer_id = -1;
	while (++layer_id < num_of_layers)
	{
		if (layer_id == INPUT_LAYER_ID)
			layer_types[layer_id] = E_LAYER_INPUT;
		else if (layer_id == OUTPUT_LAYER_ID)
			layer_types[layer_id] = E_LAYER_OUTPUT;
		else
			layer_types[layer_id] = E_LAYER_HIDDEN;
	}
	return (layer_types);
}

t_neural_network	*neural_network_init(
								const t_dataset *const *const dataset_array,
								const t_hyper_params *const hyper_params)
{
	t_neural_network	*neural_network;

	neural_network = ft_memalloc(sizeof(*neural_network));
	neural_network->layer_types = layer_types_init(hyper_params->num_of_layers);
	neural_network->layers = layers_init(neural_network->layer_types,
			dataset_array, hyper_params);
	return (neural_network);
}

static void	layers_remove(void **const *layers)
{
	size_t			i;
	t_layer_type	layer_type;

	i = -1;
	while (++i < NUM_OF_LAYERS)
	{
		layer_type = g_layer_attrs[NUM_OF_LAYERS][i].layer_type;
		if (layer_type == E_LAYER_INPUT)
			layer_remove_input((const t_layer_input **const)&(*layers)[i]);
		else if (layer_type == E_LAYER_HIDDEN)
			layer_remove_hidden((const t_layer_hidden **const)&(*layers)[i]);
		else if (layer_type == E_LAYER_OUTPUT)
			layer_remove_output((const t_layer_output **const)&(*layers)[i]);
	}
	ft_memdel((void **)layers);
	return ;
}

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

void	neural_network_mode_set(
					void *const *const layers,
					const t_layer_type *const layer_types,
					const t_dataset_type dataset_type)
{
	size_t				i;

	i = -1;
	while (++i < NUM_OF_LAYERS)
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

void	neural_network_remove(const t_neural_network **neural_network)
{
	layers_remove(&(*neural_network)->layers);
	ft_memdel((void **)&(*neural_network)->layer_types);
	ft_memdel((void **)neural_network);
	return ;
}
