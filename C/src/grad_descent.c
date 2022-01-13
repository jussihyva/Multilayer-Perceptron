/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grad_descent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 09:12:46 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/14 00:50:33 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	cost_values_print(
					const size_t iter_cnt,
					const size_t epochs,
					t_vector *cost[2])
{
	ft_printf("epoch %lu/%lu - loss: %f", iter_cnt, epochs,
		((double *)cost[E_TRAIN]->data)[0]);
	ft_printf(" - val_loss: %f\n", ((double *)cost[E_TEST]->data)[0]);
	return ;
}

static void	send_stat_to_database(
					const t_tcp_connection *const influxdb_connection,
					const t_neural_network *const neural_network,
					size_t iter_cnt,
					const t_hyper_params *const hyper_params)
{
	void *const		*layers;
	t_layer_output	*layer_output;
	size_t			num_of_layers;

	layers = neural_network->layers;
	num_of_layers = hyper_params->num_of_layers;
	layer_output = ((t_layer_output **)layers)[num_of_layers - 1];
	send_layer_stat_to_database(influxdb_connection, layers,
		neural_network->layer_types, num_of_layers);
	send_iteration_result_to_database(influxdb_connection, layer_output,
		iter_cnt);
	send_hyper_params_to_database(influxdb_connection, hyper_params);
	return ;
}

static void	train_actions(
				const t_neural_network *const neural_network,
				const size_t num_of_layers)
{
	void *const		*layers;

	layers = neural_network->layers;
	layer_mode_set(neural_network, E_TRAIN, num_of_layers);
	propagation_forward(layers, neural_network->layer_types, num_of_layers);
	propagation_backward(layers, neural_network->layer_types,
		num_of_layers);
	return ;
}

void	grad_descent(
				const t_neural_network *const neural_network,
				const t_hyper_params *const hyper_params,
				const t_tcp_connection *const influxdb_connection)
{
	void *const		*layers;
	t_layer_output	*layer_output;	
	size_t			iter_cnt;
	size_t			num_of_layers;

	num_of_layers = hyper_params->num_of_layers;
	layers = neural_network->layers;
	layer_output = ((t_layer_output **)layers)[num_of_layers - 1];
	if (!influxdb_connection)
		FT_LOG_DEBUG("Stat values are not sent to influxdb");
	iter_cnt = 0;
	while (++iter_cnt <= hyper_params->epochs)
	{
		train_actions(neural_network, num_of_layers);
		if (influxdb_connection && !(iter_cnt % 20))
			send_stat_to_database(influxdb_connection, neural_network, iter_cnt,
				hyper_params);
		layer_mode_set(neural_network, E_TEST, num_of_layers);
		propagation_forward(layers, neural_network->layer_types, num_of_layers);
		if (!(iter_cnt % 100) || iter_cnt == hyper_params->epochs)
			cost_values_print(iter_cnt, hyper_params->epochs,
				layer_output->cost);
	}
	return ;
}
