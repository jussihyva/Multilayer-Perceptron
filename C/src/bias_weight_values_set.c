/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bias_weight_values_set.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 12:58:48 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/03 11:11:59 by jkauppi          ###   ########.fr       */
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

static t_weight_bias	*get_weight_bias(
								const t_layer_type layer_type,
								const void *const layer)
{
	t_weight_bias		*weight_bias;

	if (layer_type == E_LAYER_HIDDEN)
		weight_bias = &((t_layer_hidden *)layer)->weight_bias;
	else if (layer_type == E_LAYER_OUTPUT)
		weight_bias = &((t_layer_output *)layer)->weight_bias;
	else
		weight_bias = NULL;
	return (weight_bias);
}

void	bias_weight_values_set(
						void *const *const layers,
						const t_layer_type *const layer_types,
						const t_hyper_params *const hyper_params)
{
	t_size_2d			i;
	t_weight_bias		*weight_bias;
	size_t				layer_id;
	double				*bias_data;
	double *const		*weight_table;

	layer_id = 0;
	while (++layer_id < hyper_params->num_of_layers)
	{
		weight_bias = get_weight_bias(layer_types[layer_id], layers[layer_id]);
		bias_data = (double *)weight_bias->bias->data;
		weight_table = (double **)weight_bias->weight->table;
		i.rows = -1;
		while (++i.rows < weight_bias->weight->size.rows)
		{
			bias_data[i.rows] = ((double *)hyper_params
					->bias_weight_init_values[layer_id].bias->data)[i.rows];
			i.cols = -1;
			while (++i.cols < weight_bias->weight->size.cols)
				weight_table[i.rows][i.cols] = ((double **)hyper_params
						->bias_weight_init_values[layer_id].weight
						->table)[i.rows][i.cols];
		}
	}
	print_values(weight_bias->bias, weight_bias->weight);
}
