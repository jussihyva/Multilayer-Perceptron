/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:23:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/07 14:42:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// while [ condition ]; do time ./training ; done

#include "training.h"

int	main(void)
{
	t_size_2d		size;
	t_vector		*y;
	t_matrix		*z;
	t_matrix		*y_hat;
	t_vector		*cost;

	size.rows = 10;
	size.cols = 5;
	y = ml_vector_create(size.rows);
	ml_vector_rand(y, 0, 2);
	ml_vector_print("Y", y);
	z = ml_matrix_create(size.rows, size.cols);
	y_hat = ml_matrix_create(size.rows, size.cols);
	ml_matrix_rand(z, -10, 10);
	cost = ml_vector_create(size.rows);
	ml_sigmoid(z, y_hat);
	ml_matrix_cost(y, y_hat, cost);
	ml_matrix_print("Y hat", y_hat);
	ml_vector_print("Cost", cost);
	ml_matrix_remove(&z);
	ml_matrix_remove(&y_hat);
	return (0);
}
