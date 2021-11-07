/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:23:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/07 12:08:15 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// while [ condition ]; do time ./training ; done

#include "training.h"

int	main(void)
{
	t_matrix		*z;
	t_matrix		*y_hat;
	size_t			i;
	size_t			max;
	t_size_2d		size;

	max = 1000;
	max = 10;
	size.rows = 10;
	size.cols = 5;
	i = -1;
	z = ft_matrix_create(sizeof(double), size.rows, size.cols);
	y_hat = ft_matrix_create(sizeof(double), size.rows, size.cols);
	ft_matrix_rand(z, -10, 10);
	while (++i < max)
	{
		ft_sigmoid(z, y_hat);
	}
	ft_matrix_print("Y hat", y_hat);
	ft_matrix_remove(&z);
	ft_matrix_remove(&y_hat);
	return (0);
}
