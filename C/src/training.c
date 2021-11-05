/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:23:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/05 18:01:11 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// while [ condition ]; do time ./training ; done

#include "training.h"

int	main(void)
{
	t_matrix		*z;
	t_matrix		*y_hat;
	t_matrix		*exp;
	t_matrix		*add;
	size_t			i;
	size_t			MAX;
	size_t			num_of_columns;

	MAX = 1000;
	num_of_columns = 10;
	i = -1;
	z = ft_matrix_create(sizeof(double), 1000, num_of_columns);
	y_hat = ft_matrix_create(sizeof(double), 1000, num_of_columns);
	exp = ft_matrix_create(sizeof(double), 1000, num_of_columns);
	add = ft_matrix_create(sizeof(double), 1000, num_of_columns);
	while (++i < MAX)
	{
		// y_hat = ft_sigmoid(z);
		ft_sigmoid(z, y_hat, exp, add);
		// ft_matrix_print("Y hat", y_hat);
		// ft_matrix_remove((t_matrix **)&y_hat);
	}
	ft_matrix_remove(&z);
	return (0);
}
