/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grad_descent_remove.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:16:25 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/13 12:16:35 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	grad_descent_attr_remove(
						t_grad_descent_attr **grad_descent_attr)
{
	if (*grad_descent_attr)
	{
		if ((*grad_descent_attr)->influxdb_connection)
			ft_influxdb_remove(&(*grad_descent_attr)->influxdb_connection);
		neural_network_remove(&(*grad_descent_attr)->neural_network,
			(*grad_descent_attr)->hyper_params->num_of_layers);
		hyper_params_remove((t_hyper_params **)&(*grad_descent_attr)
			->hyper_params);
		ft_memdel((void **)grad_descent_attr);
	}
	return ;
}
