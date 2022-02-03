/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grad_descent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 09:12:46 by jkauppi           #+#    #+#             */
/*   Updated: 2022/02/03 22:35:19 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	cost_values_print(
					const size_t iter_cnt,
					const size_t epochs,
					const t_layer_output *const layer_output)
{
	double		*cost_data;

	cost_data = (double *)layer_output->cost[E_TRAIN]->data;
	ft_printf("epoch %lu/%lu - loss: %f", iter_cnt, epochs, cost_data[0]);
	cost_data = (double *)layer_output->cost[E_TEST]->data;
	ft_printf(" - val_loss: %f\n", cost_data[0]);
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

static t_bool	is_early_stop(const size_t iter_cnt, const t_vector *const cost)
{
	static double	prev_cost = 0;
	double			current_cost;
	t_bool			early_stop;

	early_stop = E_FALSE;
	if (!(iter_cnt % 100))
	{
		current_cost = ((double *)cost->data)[0];
		if (prev_cost && ((current_cost - prev_cost) / current_cost > 0.005))
		{
			early_stop = E_TRUE;
			FT_LOG_INFO("Early stop is valid!");
		}
		prev_cost = ((double *)cost->data)[0];
	}
	return (early_stop);
}

size_t	grad_descent(
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
	while (++iter_cnt <= hyper_params->epochs
		&& !is_early_stop(iter_cnt, layer_output->cost[E_TEST]))
	{
		train_actions(neural_network, num_of_layers);
		if (influxdb_connection && !(iter_cnt % 20))
			send_stat_to_database(influxdb_connection, neural_network, iter_cnt,
				hyper_params);
		layer_mode_set(neural_network, E_TEST, num_of_layers);
		propagation_forward(layers, neural_network->layer_types, num_of_layers);
		if (!(iter_cnt % 100) || iter_cnt == hyper_params->epochs)
			cost_values_print(iter_cnt, hyper_params->epochs, layer_output);
	}
	return (iter_cnt);
}
