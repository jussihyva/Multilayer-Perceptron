/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_stat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:15:14 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/10 13:08:35 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static const char	*get_layer_stat(
					const t_weight_bias *const weight_bias,
					const t_hyper_params *const hyper_params,
					const size_t layer_id)
{
	char			*line;

	line = ft_strdup("");
	bias_stat_add(&line, weight_bias->bias, hyper_params, layer_id);
	weight_stat_add(&line, weight_bias->weight, hyper_params, layer_id);
	return (line);
}

const char	*get_layer_stat_hidden(
					const t_layer_hidden *const layer,
					const size_t layer_id)
{
	const char	*line;

	line = get_layer_stat(&layer->weight_bias, layer->hyper_params, layer_id);
	return (line);
}

const char	*get_layer_stat_output(
					const t_layer_output *const layer,
					const size_t layer_id)
{
	const char	*line;

	line = get_layer_stat(&layer->weight_bias, layer->hyper_params, layer_id);
	return (line);
}
