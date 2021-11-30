/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logistic_regression.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhani <juhani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 11:55:45 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/30 15:37:46 by juhani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

t_logistic_reg_attr	*logistic_reg_init(const t_dataset *const dataset)
{
	t_logistic_reg_attr		*logistic_reg_attr;

	logistic_reg_attr = ft_memalloc(sizeof(*logistic_reg_attr));
	logistic_reg_attr->neural_network = neural_network_init(dataset);
	return (logistic_reg_attr);
}

void	logistic_regression(const t_layer *const layer)
{
	linear_function(layer);
	ml_sigmoid(layer->z, layer->a_output);
	if (ft_logging_level() <= LOG_DEBUG)
	{
		ft_printf("LAYER: %lu\n", layer->num_of_nodes);
		ml_matrix_print(" (A) Output", layer->a_output);
	}
	return ;
}

void	logistic_reg_attr_remove(
						t_logistic_reg_attr **logistic_reg_attr)
{
	const t_layer		*layer;
	t_neural_network	*neural_network;
	size_t				i;

	neural_network = (*logistic_reg_attr)->neural_network;
	i = -1;
	while (++i < NUM_OF_LAYERS)
	{
		layer = neural_network->layers[i];
		ml_matrix_remove((t_matrix **)&layer->weight);
		ml_vector_remove((t_vector **)&layer->bias);
		ml_matrix_remove((t_matrix **)&layer->z);
		ml_matrix_remove((t_matrix **)&layer->a_output);
		ml_matrix_remove((t_matrix **)&layer->d_weight);
		ml_vector_remove((t_vector **)&layer->d_bias);
		ml_matrix_remove((t_matrix **)&layer->d_z);
		ft_memdel((void **)&layer);
	}
	ft_memdel((void **)&neural_network->layers);
	ft_memdel((void **)&(*logistic_reg_attr)->neural_network);
	ft_memdel((void **)logistic_reg_attr);
	return ;
}
