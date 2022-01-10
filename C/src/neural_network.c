/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neural_network.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:15:53 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/10 17:56:33 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	**layers_init(
							const t_layer_type *const layer_types,
							t_dataset **dataset_array,
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
		layer_types[layer_id] = set_layer_type(layer_id, num_of_layers);
	return (layer_types);
}

t_neural_network	*neural_network_init(
								t_dataset **dataset_array,
								const t_hyper_params *const hyper_params)
{
	t_neural_network	*neural_network;

	neural_network = ft_memalloc(sizeof(*neural_network));
	neural_network->layer_types = layer_types_init(hyper_params->num_of_layers);
	neural_network->layers = layers_init(neural_network->layer_types,
			dataset_array, hyper_params);
	if (hyper_params->weight_init_mode == E_TRAINED)
		bias_weight_values_set(neural_network->layers,
			neural_network->layer_types, hyper_params);
	layer_mode_set(neural_network, E_TRAIN,
		hyper_params->num_of_layers);
	return (neural_network);
}
