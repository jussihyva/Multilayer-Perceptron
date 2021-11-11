/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:23:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/11 14:27:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// while [ condition ]; do time ./training ; done

#include "training.h"

int	main(void)
{
	t_size_2d			size;
	t_matrix			*input;
	t_matrix			*weight;
	t_vector			*bias;
	t_matrix			*y;
	t_matrix			*z;
	t_matrix			*y_hat;
	t_vector			*cost;
	size_t				num_of_examples;
	size_t				num_of_functions;
	size_t				num_of_nodes;
	t_read_attributes	*read_attributes;

	read_attributes = ft_read_file("../Data/data.csv", E_CSV);
	num_of_examples = 5;
	num_of_functions = 10;
	num_of_nodes = num_of_functions;
	size.rows = 10;
	size.cols = 5;
	y = ml_matrix_create(num_of_nodes, num_of_examples);
	ml_matrix_rand(y, 0, 2);
	ml_matrix_print("Y", y);
	input = ml_matrix_create(num_of_functions, num_of_examples);
	ml_matrix_rand(input, -10, 10);
	weight = ml_matrix_create(num_of_nodes, num_of_functions);
	ml_matrix_rand(weight, -10, 10);
	bias = ml_vector_create(num_of_functions);
	ml_vector_rand(bias, 0, 2);
	z = ml_matrix_create(num_of_nodes, num_of_examples);
	ml_matrix_linear_function(input, weight, bias, z);
	ml_matrix_print("Z", z);
	y_hat = ml_matrix_create(num_of_nodes, num_of_examples);
	ml_sigmoid(z, y_hat);
	cost = ml_vector_create(num_of_nodes);
	ml_matrix_cost(y, y_hat, cost);
	// ml_matrix_print("Y hat", y_hat);
	// ml_vector_print("Cost", cost);
	ml_matrix_remove(&z);
	ml_matrix_remove(&y_hat);
	return (0);
}
