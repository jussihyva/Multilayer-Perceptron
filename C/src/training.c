/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:23:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/04 18:51:40 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "training.h"

int	main(void)
{
	t_matrix		*z;
	const t_matrix	*y_hat;

	z = ft_matrix_create(sizeof(double), 5, 10);
	y_hat = ft_sigmoid(z);
	ft_matrix_print("Y hat", y_hat);
	ft_matrix_remove((t_matrix **)&y_hat);
	ft_matrix_remove(&z);
	return (0);
}
