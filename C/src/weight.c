/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weight.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:34:47 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/07 11:43:40 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	weight_update(const size_t layer_id, const t_matrix *const weight,
				const t_matrix *const d_weight, const double learning_rate)
{
	t_size_2d	i;
	size_t		total_size;
	size_t		num_of_nodes;
	size_t		num_of_activation_inputs;
	size_t		prev_layer_id;

	prev_layer_id = layer_id - 1;
	num_of_nodes = g_layer_attrs[layer_id].nodes;
	num_of_activation_inputs = g_layer_attrs[prev_layer_id].nodes;
	total_size = num_of_nodes * num_of_activation_inputs;
	i.rows = -1;
	while (++i.rows < num_of_nodes)
	{
		i.cols = -1;
		while (++i.cols < num_of_activation_inputs)
			((double **)weight->table)[i.rows][i.cols] -= learning_rate
				* ((double **)d_weight->table)[i.rows][i.cols];
	}
	return ;
}