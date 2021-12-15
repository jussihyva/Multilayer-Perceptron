/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neural_network.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:15:53 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/16 00:19:06 by jkauppi          ###   ########.fr       */
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

	layers = ft_memalloc(sizeof(*layers) * NUM_OF_LAYERS);
	i = -1;
	while (++i < NUM_OF_LAYERS)
		layers[i] = layer_init(i, layer_types[i], dataset_array, hyper_params);
	return (layers);
}

static const t_layer_type	*layer_types_init(void)
{
	size_t				layer_id;
	t_layer_type		*layer_types;

	layer_types = ft_memalloc(sizeof(*layer_types) * NUM_OF_LAYERS);
	layer_id = -1;
	while (++layer_id < NUM_OF_LAYERS)
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
	neural_network->layer_types = layer_types_init();
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

void	neural_network_remove(const t_neural_network **neural_network)
{
	layers_remove(&(*neural_network)->layers);
	ft_memdel((void **)&(*neural_network)->layer_types);
	ft_memdel((void **)neural_network);
	return ;
}
