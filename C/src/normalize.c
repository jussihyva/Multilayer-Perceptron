/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhani <juhani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:13:10 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/30 22:50:27 by juhani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	calculate(
				const t_matrix *const input,
				const t_matrix *const output,
				const double *const min,
				const double *const max)
{
	t_size_2d	i;
	double		**input_table;
	double		**output_table;
	double		range;

	input_table = (double **)input->table;
	output_table = (double **)output->table;
	i.rows = -1;
	while (++i.rows < input->size.rows)
	{
		i.cols = -1;
		range = max[i.rows] - min[i.rows];
		while (++i.cols < input->size.cols)
		{
			output_table[i.rows][i.cols]
				= input_table[i.rows][i.cols] - min[i.rows];
			output_table[i.rows][i.cols] /= range;
		}
	}
	return ;
}

void	normalize(const t_matrix *const input, const t_matrix *const output)
{
	const t_vector		*min;
	const t_vector		*max;

	min = ml_matrix_min(input);
	max = ml_matrix_max(input);
	if (ft_logging_level() <= LOG_TRACE)
	{
		ml_vector_print("MIN", min);
		ml_vector_print("MAX", max);
	}
	calculate(input, output, min->data, max->data);
	ml_vector_remove((t_vector **)&min);
	ml_vector_remove((t_vector **)&max);
	return ;
}
