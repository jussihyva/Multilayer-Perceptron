/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_prime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:40:49 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/05 16:51:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	g_prime_sigmoid(const t_matrix *const a, const t_matrix *const g_prime)
{
	const double	**a_table;
	double			**g_prime_table;
	t_size_2d		i;

	a_table = (const double **)a->table;
	g_prime_table = (double **)g_prime->table;
	i.rows = -1;
	while (++i.rows < a->size.rows)
	{
		i.cols = -1;
		while (++i.cols < a->size.cols)
			g_prime_table[i.rows][i.cols] = a_table[i.rows][i.cols]
				* (1 - a_table[i.rows][i.cols]);
	}
	return ;
}
