/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:08:16 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/17 13:00:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	layer_print_input(const t_layer_input *const layer)
{
	ft_printf("LAYER: %lu\n", layer->id);
	ml_matrix_print(" X ", layer->x);
	ml_matrix_print(" A ", layer->a);
	return ;
}

void	layer_print_output(const t_layer_output *const layer)
{
	ft_printf("LAYER: %lu\n", layer->id);
	ml_matrix_print(" (Y_hat) Prediction", layer->y_hat);
	ml_matrix_print(" (Y) Observation", layer->y);
	ml_vector_print(" Cost (TRAIN)", layer->cost[E_TRAIN]);
	ml_vector_print(" Cost (TEST)", layer->cost[E_TEST]);
	return ;
}
