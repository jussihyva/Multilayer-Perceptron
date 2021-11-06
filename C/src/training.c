/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:23:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/06 09:29:43 by jkauppi          ###   ########.fr       */
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
	size_t			num_of_columns;

	max = 1000;
	num_of_columns = 10000;
	i = -1;
	z = ft_matrix_create(sizeof(double), 1000, num_of_columns);
	y_hat = ft_matrix_create(sizeof(double), 1000, num_of_columns);
	while (++i < max)
	{
		ft_sigmoid(z, y_hat);
	}
	ft_matrix_print("Y hat", y_hat);
	ft_matrix_remove(&z);
	ft_matrix_remove(&y_hat);
	return (0);
}
