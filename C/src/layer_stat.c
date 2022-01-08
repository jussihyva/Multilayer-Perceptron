/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_stat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:15:14 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/09 00:16:08 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

const char	*get_layer_stat_hidden(
					const t_layer_hidden *const layer,
					const size_t layer_id)
{
	char			*line;

	line = ft_strdup("");
	bias_stat_add(&line, layer->weight_bias.bias, layer->hyper_params,
		layer_id);
	weight_stat_add(&line, layer->weight_bias.weight, layer->hyper_params,
		layer_id);
	return (line);
}

const char	*get_layer_stat_output(
					const t_layer_output *const layer,
					const size_t layer_id)
{
	char			*line;

	line = ft_strdup("");
	bias_stat_add(&line, layer->weight_bias.bias, layer->hyper_params,
		layer_id);
	weight_stat_add(&line, layer->weight_bias.weight, layer->hyper_params,
		layer_id);
	return (line);
}
