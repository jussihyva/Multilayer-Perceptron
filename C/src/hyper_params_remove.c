/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper_params_remove.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 23:30:34 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/11 00:15:40 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	hyper_params_remove(t_hyper_params **hyper_params)
{
	size_t		i;

	ft_memdel((void **)&(*hyper_params)->activation_types);
	ft_memdel((void **)&(*hyper_params)->num_of_nodes);
	if ((*hyper_params)->bias_weight_init_values)
	{
		i = -1;
		while (++i < (*hyper_params)->num_of_layers)
		{
			if ((*hyper_params)->bias_weight_init_values[i].bias)
				ml_vector_remove(&(*hyper_params)
					->bias_weight_init_values[i].bias);
			if ((*hyper_params)->bias_weight_init_values[i].weight)
				ml_matrix_remove(&(*hyper_params)
					->bias_weight_init_values[i].weight);
		}
		ft_memdel((void **)&(*hyper_params)->bias_weight_init_values);
	}
	ft_memdel((void **)hyper_params);
	return ;
}
