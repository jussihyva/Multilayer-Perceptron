/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bias_weight_values_read.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 08:39:40 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/06 21:49:44 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	bias_weight_values_read(
						t_weight_bias *const bias_weight,
						const char *const *const *const row_array,
						size_t *const row_id)
{
	double				**weight_table;
	double				*bias_data;
	t_size_2d			size;
	const char *const	*row;

	bias_data = (double *)bias_weight->bias->data;
	weight_table = (double **)bias_weight->weight->table;
	size.rows = -1;
	while (++size.rows < bias_weight->weight->size.rows)
	{
		row = row_array[*row_id];
		size.cols = -1;
		string_convert_and_validate(row[size.cols + 1], E_DOUBLE,
			&bias_data[size.rows]);
		while (++size.cols < bias_weight->weight->size.cols)
			string_convert_and_validate(row[size.cols + 1], E_DOUBLE,
				&weight_table[size.rows][size.cols]);
		(*row_id)++;
	}
	return ;
}
