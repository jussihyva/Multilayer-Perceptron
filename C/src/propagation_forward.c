/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   propagation_forward.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:04:22 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/06 15:11:35 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	propagation_forward(const t_neural_network *const neural_network)
{
	size_t				i;
	const t_matrix		*activation_input;
	const void			**layers;

	layers = neural_network->layers;
	i = -1;
	while (++i < NUM_OF_LAYERS)
	{
		activation_input = get_activation_input(neural_network, i);
		if (neural_network->layer_types[i] == E_LAYER_INPUT)
			propagation_forward_input(layers[i]);
		else if (neural_network->layer_types[i] == E_LAYER_OUTPUT)
			propagation_forward_output(layers[i], activation_input);
		else
			propagation_forward_hidden(layers[i], activation_input);
	}
	return ;
}
