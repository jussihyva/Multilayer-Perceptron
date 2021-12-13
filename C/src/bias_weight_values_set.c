/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bias_weight_values_set.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 12:58:48 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/13 01:58:27 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	print_values(
					const t_vector *const bias,
					const t_matrix *const weight)
{
	if (ft_logging_level() <= LOG_INFO)
	{
		ml_vector_print("BIAS", bias);
		ml_matrix_print("WEIGHT", weight);
	}
	return ;
}

void	bias_weight_values_set(
						const void *const *const layers,
						const t_layer_type *const layer_types,
						const char *const weight_bias_file)
{
	t_file_attr		*file_attr;
	t_size_2d		i;
	char			*endptr;
	double			value;
	t_weight_bias	*weight_bias;
	size_t			layer_id;
	const char		*const *row;
	size_t			row_id;

	endptr = NULL;
	file_attr = ft_read_file(weight_bias_file, E_CSV);
	layer_id = 0;
	row_id = 3;
	while (++layer_id < NUM_OF_LAYERS)
	{
		if (layer_types[layer_id] == E_LAYER_HIDDEN)
			weight_bias = &((t_layer_hidden *)layers[layer_id])->weight_bias;
		else if (layer_types[layer_id] == E_LAYER_OUTPUT)
			weight_bias = &((t_layer_output *)layers[layer_id])->weight_bias;
		i.rows = -1;
		while (++i.rows < weight_bias->weight->size.rows && row_id < file_attr->rows)
		{
			row = file_attr->row_array[row_id];
			i.cols = 0;
			value = strtod(row[i.cols], &endptr);
			((double *)weight_bias->bias->data)[i.rows] = value;
			while (++i.cols <= weight_bias->weight->size.cols)
			{
				value = strtod(row[i.cols], &endptr);
				((double **)weight_bias->weight->table)[i.rows][i.cols - 1] = value;
			}
			row_id++;
		}
	}
	file_attr_remove(&file_attr);
	print_values(weight_bias->bias, weight_bias->weight);
	return ;
}
