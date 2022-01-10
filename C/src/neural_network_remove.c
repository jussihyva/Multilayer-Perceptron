/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neural_network_remove.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:49:14 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/10 17:56:42 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	layers_remove(
					void **const *layers,
					const t_layer_type *const layer_types,
					const size_t num_of_layers)
{
	size_t			i;

	i = -1;
	while (++i < num_of_layers)
	{
		if (layer_types[i] == E_LAYER_INPUT)
			layer_remove_input((t_layer_input **)&(*layers)[i]);
		else if (layer_types[i] == E_LAYER_HIDDEN)
			layer_remove_hidden((t_layer_hidden **)&(*layers)[i]);
		else if (layer_types[i] == E_LAYER_OUTPUT)
			layer_remove_output((t_layer_output **)&(*layers)[i]);
	}
	ft_memdel((void **)layers);
	return ;
}

void	neural_network_remove(
					const t_neural_network **neural_network,
					const size_t num_of_layers)
{
	layers_remove(&(*neural_network)->layers, (*neural_network)->layer_types,
		num_of_layers);
	ft_memdel((void **)&(*neural_network)->layer_types);
	ft_memdel((void **)neural_network);
	return ;
}
