/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bias_weight_values_read.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 08:39:40 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/06 08:47:21 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

// void	bias_weight_values_read(t_weight_bias *const bias_weight)
// {
// 	double				**weight_table;
// 	double				*bias_data;
// 	t_size_2d			size;
// 	const char *const	*row;

// 	bias_data = (double *)bias_weight->bias->data;
// 	weight_table = (double **)bias_weight->weight->table;
// 	size.rows = -1;
// 	while (++size.rows < num_of_nodes[layer_id])
// 	{
// 		row = file_attr->row_array[row_id];
// 		size.cols = -1;
// 		read_and_validate(row[size.cols + 1], E_DOUBLE,
// 			&bias_data[size.rows]);
// 		while (++size.cols < num_of_nodes[layer_id - 1])
// 			read_and_validate(row[size.cols + 1], E_DOUBLE,
// 				&weight_table[size.rows][size.cols]);
// 		row_id++;
// 	}
// 	return ;
// }
