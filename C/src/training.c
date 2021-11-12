/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:23:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/12 20:25:01 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// while [ condition ]; do time ./training ; done

#include "training.h"

int	main(void)
{
	t_dataset			*dataset;
	t_matrix			*weight;
	t_vector			*bias;
	t_matrix			*z;
	t_matrix			*y_hat;
	t_vector			*cost;
	t_vector			*derivative_z;
	t_matrix			*derivative_w;
	size_t				num_of_examples;
	size_t				num_of_functions;
	size_t				num_of_nodes;

	dataset = read_dataset("../Data/data.csv");
	// ml_matrix_print("X", dataset->x);
	num_of_examples = dataset->x->size.cols;
	num_of_functions = dataset->x->size.rows;
	num_of_nodes = 2;
	weight = ml_matrix_create(num_of_nodes, num_of_functions);
	ml_matrix_rand(weight, 0, 1);
	bias = ml_vector_create(num_of_functions);
	ml_vector_rand(bias, 0, 1);
	z = ml_matrix_create(num_of_nodes, num_of_examples);
	ml_matrix_linear_function(dataset->x, weight, bias, z);
	// ml_matrix_print("Z", z);
	y_hat = ml_matrix_create(num_of_nodes, num_of_examples);
	ml_sigmoid(z, y_hat);
	cost = ml_vector_create(num_of_nodes);
	ml_matrix_cost(dataset->y, y_hat, cost);
	// ml_matrix_print("Y hat", y_hat);
	// ml_matrix_print("Y", dataset->y);
	ml_vector_print("Cost", cost);
	derivative_z = calculate_derivative_of_z(y_hat, dataset->y);
	ml_vector_print("dz", derivative_z);
	derivative_w = calculate_derivative_of_w(dataset->x, derivative_z);
	ml_matrix_print("dw", derivative_w);
	ml_matrix_remove(&z);
	ml_matrix_remove(&y_hat);
	ml_matrix_remove(&weight);
	ml_vector_remove(&bias);
	ml_vector_remove(&cost);
	dataset_remove(&dataset);
	return (0);
}
