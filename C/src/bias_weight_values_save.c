/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bias_weight_values_save.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:40:09 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/02 20:15:14 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static size_t	weight_values_add(
						t_queue *const queue,
						const double *const weight_row,
						const size_t columns)
{
	size_t		string_length;
	char		*substring;
	size_t		i;

	string_length = 0;
	i = -1;
	while (++i < columns)
	{
		ft_enqueue(queue, (void *)ft_strdup(","));
		string_length++;
		substring = ft_strnew(SUB_STRING_MAX_LENGTH);
		ft_sprintf(substring, "%f", weight_row[i]);
		ft_enqueue(queue, (void *)substring);
		string_length += ft_strlen(substring);
	}
	return (string_length);
}

static char	*strings_merge(
					t_queue *const queue,
					const size_t string_length)
{
	char		*str;
	const char	*substring;

	str = ft_strnew(string_length);
	while (!ft_is_queue_empty(queue))
	{
		substring = (char *)ft_dequeue(queue);
		ft_strcat(str, substring);
		ft_strdel((char **)&substring);
	}
	return (str);
}

static char	*yaml_string_create(
							const double *const weight_row,
							const double bias,
							const size_t columns)
{
	t_queue		*queue;
	char		*substring;
	size_t		string_length;
	char		*str;

	queue = ft_queue_init();
	string_length = 0;
	substring = ft_strnew(SUB_STRING_MAX_LENGTH);
	ft_sprintf(substring, "%f", bias);
	ft_enqueue(queue, (void *)substring);
	string_length += ft_strlen(substring);
	string_length += weight_values_add(queue, weight_row, columns);
	ft_enqueue(queue, (void *)ft_strdup("\n"));
	string_length++;
	str = strings_merge(queue, string_length);
	ft_queue_remove(&queue);
	return (str);
}

void	bias_weight_values_save(
						void *const *layers,
						const t_layer_type *const layer_types,
						const char *const weight_bias_file,
						const t_hyper_params *const hyper_params)
{
	t_read_attr		read_attr;
	ssize_t			len;
	size_t			i;
	size_t			layer_id;
	t_weight_bias	*weight_bias;

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
	layer_id = 0;
	while (++layer_id < hyper_params->num_of_layers)
	{
		if (layer_types[layer_id] == E_LAYER_HIDDEN)
			weight_bias = &((t_layer_hidden *)layers[layer_id])->weight_bias;
		else if (layer_types[layer_id] == E_LAYER_OUTPUT)
			weight_bias = &((t_layer_output *)layers[layer_id])->weight_bias;
		i = -1;
		while (++i < weight_bias->weight->size.rows)
		{
			read_attr.line
				= yaml_string_create(((double **)weight_bias->weight->table)[i],
					((double *)weight_bias->bias->data)[i],
					weight_bias->weight->size.cols);
			read_attr.ret = write(read_attr.fd, read_attr.line,
					ft_strlen(read_attr.line));
			ft_strdel((char **)&read_attr.line);
		}
	}
	read_attr.ret = close(read_attr.fd);
	return ;
}
