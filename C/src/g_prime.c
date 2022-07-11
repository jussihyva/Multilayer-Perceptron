/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_prime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:40:49 by jkauppi           #+#    #+#             */
/*   Updated: 2022/07/11 11:21:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	g_prime_sigmoid(
					const t_matrix *const a,
					const t_matrix *const g_prime)
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

static void	g_prime_relu(
					const t_matrix *const z,
					const t_matrix *const g_prime)
{
	const double	**z_table;
	double			**g_prime_table;
	double			value;
	t_size_2d		i;

	z_table = (const double **)z->table;
	g_prime_table = (double **)g_prime->table;
	i.rows = -1;
	while (++i.rows < z->size.rows)
	{
		i.cols = -1;
		while (++i.cols < z->size.cols)
		{
			value = z_table[i.rows][i.cols];
			if (value <= 0)
				g_prime_table[i.rows][i.cols] = 0;
			else if (value > 0)
				g_prime_table[i.rows][i.cols] = 1;
			else
				FT_LOG_ERROR("g'prime relu is undefined");
		}
	}
	return ;
}

void	g_prime(
			const t_matrix *const z,
			const t_matrix *const a,
			const t_matrix *const g_prime,
			const t_activation_type activation_type)
{
	if (activation_type == E_SIGMOID)
		g_prime_sigmoid(a, g_prime);
	else if (activation_type == E_RELU)
		g_prime_relu(z, g_prime);
	else
		FT_LOG_ERROR("g'prime calculatio is not implemented");
	return ;
}
