/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   propagation_backward.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:23:05 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/03 11:04:03 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	propagation_backward_input(
								const void *const layer,
								const t_matrix *const weight,
								const t_matrix *const d_z)
{
	t_layer_input	*layer_input;

	layer_input = (t_layer_input *)layer;
	(void)weight;
	(void)d_z;
	return ;
}

static void	propagation_backward_hidden(
								const void *const layer,
								const t_matrix *const weight,
								const t_matrix *const d_z)
{
	t_layer_hidden	*layer_input;

	layer_input = (t_layer_hidden *)layer;
	// layer_input->z * (1 - layer_input->z);
	(void)layer_input->d_z;
	(void)weight;
	(void)d_z;
	return ;
}

static void	propagation_backward_output(
								const void *const layer,
								const t_matrix *const weight,
								const t_matrix *const d_z)
{
	t_layer_hidden	*layer_input;

	layer_input = (t_layer_hidden *)layer;
	// layer_input->z * (1 - layer_input->z);
	(void)layer_input->d_z;
	(void)weight;
	(void)d_z;
	return ;
}

void	set_propagation_backward_functions(
		t_fn_propagation_backward *const fn_propagation_backward)
{
	size_t		i;

	i = -1;
	while (++i < NUM_OF_LAYERS)
	{
		if (!i)
			fn_propagation_backward[i] = propagation_backward_input;
		else if (i == (NUM_OF_LAYERS - 1))
			fn_propagation_backward[i] = propagation_backward_output;
		else
			fn_propagation_backward[i] = propagation_backward_hidden;
	}
	return ;
}
