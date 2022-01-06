/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper_params_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 13:26:53 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/06 08:28:42 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static size_t	*get_number_of_nodes_default(const size_t num_of_layers)
{
	const t_layer_profile	*layer_profile;
	size_t					*num_of_nodes;
	size_t					i;

	num_of_nodes = ft_memalloc(sizeof(*num_of_nodes) * num_of_layers);
	layer_profile = g_layer_attrs[num_of_layers];
	i = -1;
	while (++i < num_of_layers)
		num_of_nodes[i] = layer_profile[i].nodes;
	return (num_of_nodes);
}

static t_activation_type	*get_activation_types(const size_t num_of_layers)
{
	const t_layer_profile	*layer_profile;
	t_activation_type		*activation_types;
	size_t					i;

	activation_types = ft_memalloc(sizeof(*activation_types) * num_of_layers);
	layer_profile = g_layer_attrs[num_of_layers];
	i = -1;
	while (++i < num_of_layers)
		activation_types[i] = layer_profile[i].activation_type;
	return (activation_types);
}

t_hyper_params	*hyper_params_init(
						const char *const weight_bias_file,
						const t_hyper_params *const input_hyper_params,
						const size_t num_of_input_functions,
						const size_t num_of_output_functions)
{
	t_hyper_params	*hyper_params;

	hyper_params = ft_memalloc(sizeof(*hyper_params));
	hyper_params->split_order = input_hyper_params->split_order;
	hyper_params->epochs = input_hyper_params->epochs;
	hyper_params->learning_rate = input_hyper_params->learning_rate;
	hyper_params->weight_init_mode = input_hyper_params->weight_init_mode;
	if (input_hyper_params->weight_init_mode == E_TRAINED)
		get_hyper_params_from_file(weight_bias_file, num_of_input_functions,
			num_of_output_functions, hyper_params);
	else
	{
		hyper_params->num_of_layers = input_hyper_params->num_of_layers;
		hyper_params->num_of_nodes
			= get_number_of_nodes_default(hyper_params->num_of_layers);
	}
	hyper_params->activation_types
		= get_activation_types(hyper_params->num_of_layers);
	return (hyper_params);
}
