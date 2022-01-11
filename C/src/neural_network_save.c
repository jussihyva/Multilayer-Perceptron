/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neural_network_save.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:34:25 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/11 12:49:16 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	neural_network_save(void *const *const layers,
							const t_layer_type *const layer_types,
							const char *const weight_bias_file,
							const t_hyper_params *const hyper_params)
{
	t_read_attr		read_attr;
	ssize_t			len;
	size_t			layer_id;

	remove(weight_bias_file);
	read_attr.fd = open(weight_bias_file, O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
	read_attr.line = ft_strnew(SUB_STRING_MAX_LENGTH);
	len = ft_sprintf(read_attr.line, "%d\n", hyper_params->num_of_layers);
	read_attr.ret = write(read_attr.fd, read_attr.line, len);
	layer_id = 0;
	while (++layer_id < (hyper_params->num_of_layers - 1))
	{
		len = ft_sprintf(read_attr.line, "%d\n",
				hyper_params->num_of_nodes[layer_id]);
		read_attr.ret = write(read_attr.fd, read_attr.line, len);
	}
	ft_strdel((char **)&read_attr.line);
	bias_weight_values_save(layers, layer_types, &read_attr, hyper_params);
	read_attr.ret = close(read_attr.fd);
	return ;
}
