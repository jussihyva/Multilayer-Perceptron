/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 20:44:48 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/07 11:12:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

t_layer_type	set_layer_type(const size_t id, const size_t num_of_layers)
{
	t_layer_type	layer_type;

	if (id == 0)
		layer_type = E_LAYER_INPUT;
	else if (id == num_of_layers - 1)
		layer_type = E_LAYER_OUTPUT;
	else
		layer_type = E_LAYER_HIDDEN;
	return (layer_type);
}

const t_matrix	*get_activation_input(
							void *const layer,
							const t_layer_type layer_type)
{
	const t_matrix		*activation_input;

	activation_input = NULL;
	if (layer_type == E_LAYER_HIDDEN)
		activation_input = ((t_layer_hidden *)layer)->a;
	else if (layer_type == E_LAYER_INPUT)
		activation_input = ((t_layer_input *)layer)->a;
	else
		FT_LOG_FATAL("Layer type %u is not supported", layer_type);
	return (activation_input);
}
