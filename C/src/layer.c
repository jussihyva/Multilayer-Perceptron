/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 20:44:48 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/02 20:45:35 by jkauppi          ###   ########.fr       */
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
