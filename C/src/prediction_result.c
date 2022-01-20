/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prediction_result.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 10:46:01 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/20 12:59:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	print_result(
					const t_dataset *const dataset,
					const t_layer_output *layer_output)
{
	ml_matrix_print("Observed", dataset->y);
	ml_matrix_print("Softmax", layer_output->softmax);
	return ;
}

static void	binary_cross_entropy_print(const t_vector *const cost)
{
	ft_printf("E(Benign)=%.2f\n", ((double *)cost->data)[0]);
	ft_printf("E(Malignant)=%.2f\n", ((double *)cost->data)[1]);
	return ;
}

void	prediction_result(t_grad_descent_attr *grad_descent_attr)
{
	const t_neural_network		*neural_network;
	size_t						num_of_layers;
	t_layer_output				*layer_output;
	t_bool						*accuracy_array;

	neural_network = grad_descent_attr->neural_network;
	num_of_layers = grad_descent_attr->hyper_params->num_of_layers;
	layer_output = (t_layer_output *)neural_network->layers[num_of_layers - 1];
	ml_softmax(layer_output->y_hat, layer_output->softmax);
	if (grad_descent_attr->influxdb_connection)
		send_softmax_result_to_database(grad_descent_attr
			->influxdb_connection, layer_output->softmax);
	else
		FT_LOG_DEBUG("Softmax values are not sent to influxdb");
	ml_argmax(layer_output->softmax, layer_output->argmax,
		layer_output->argmax_values);
	if (ft_logging_level() <= LOG_INFO)
		print_result(grad_descent_attr->dataset, layer_output);
	binary_cross_entropy_print(layer_output->cost[E_TRAIN]);
	accuracy_array = prediction_validate(grad_descent_attr->dataset->y,
			layer_output->argmax);
	return ;
}
