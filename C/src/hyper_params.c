/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:37:31 by juhani            #+#    #+#             */
/*   Updated: 2022/01/01 16:13:39 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

t_weight_init_mode	set_weight_init_mode(const t_argc_argv *const argc_argv)
{
	t_weight_init_mode		weight_init_mode;
	const char				*arg;

	weight_init_mode = E_ZERO;
	arg = argc_argv->argv[argc_argv->i];
	if (ft_strequ(arg, "0"))
		weight_init_mode = E_ZERO;
	else if (ft_strequ(arg, "1"))
		weight_init_mode = E_RAND_0_TO_1;
	else
		FT_LOG_ERROR("Weight mode %s is not supported.", arg);
	return (weight_init_mode);
}

static t_dataset_split_mode	set_split_mode(const char mode_char)
{
	t_dataset_split_mode	dataset_split_mode;

	dataset_split_mode = 0;
	if (mode_char == 'B')
		dataset_split_mode = E_BEGIN;
	else if (mode_char == 'E')
		dataset_split_mode = E_END;
	else if (mode_char == 'R')
		dataset_split_mode = E_RAND;
	else
		FT_LOG_ERROR("Split mode %c is not supported.", mode_char);
	return (dataset_split_mode);
}

const t_dataset_split_order	*set_dataset_split_mode(
								const t_argc_argv *const argc_argv)
{
	const char				*arg;
	char					*endptr;
	t_dataset_split_order	*dataset_split_order;
	char					mode_char;

	dataset_split_order = ft_memalloc(sizeof(*dataset_split_order));
	arg = argc_argv->argv[argc_argv->i];
	mode_char = *arg;
	arg++;
	dataset_split_order->dataset_split_mode = set_split_mode(mode_char);
	errno = 0;
	dataset_split_order->extra_info = strtoul(arg, &endptr, 10);
	if (errno != 0 || *endptr != '\0')
		FT_LOG_ERROR("Value of param -s is not valid");
	else if (dataset_split_order->extra_info > 100)
		FT_LOG_ERROR("Maximum value for split mode (-s) is 100");
	return (dataset_split_order);
}

size_t	set_number_of_epochs(const t_argc_argv *const argc_argv)
{
	const char		*arg;
	char			*endptr;
	size_t			epochs;

	errno = 0;
	arg = argc_argv->argv[argc_argv->i];
	epochs = ft_strtoi(arg, &endptr, 10);
	if (errno != 0 || *endptr != '\0')
		FT_LOG_ERROR("Value of param -E is not valid");
	if (epochs > 100000)
		FT_LOG_ERROR("Maximum value for epochs (-E) is "
			"100000 (100 thousand)");
	if (epochs <= 0)
		FT_LOG_ERROR("Minimum value for epochs (-E) is >0");
	return (epochs);
}

double	set_learning_rate(const t_argc_argv *const argc_argv)
{
	const char		*arg;
	char			*endptr;
	double			learning_rate;

	errno = 0;
	arg = argc_argv->argv[argc_argv->i];
	learning_rate = strtod(arg, &endptr);
	if (errno != 0 || *endptr != '\0')
		FT_LOG_ERROR("Value of param -A is not valid");
	if (learning_rate > 1)
		FT_LOG_ERROR("Maximum value for learning rate (-A) is 1");
	if (learning_rate <= 0)
		FT_LOG_ERROR("Minimum value for learning rate (-A) is >0");
	return (learning_rate);
}

static size_t	influxdb_tags_add(const char **const tags_set)
{
	t_queue		*string_queue;
	char		*tag_value_pair;
	size_t		length;

	string_queue = ft_queue_init();
	length = 0;
	length++;
	ft_enqueue(string_queue, ft_strdup(","));
	tag_value_pair = ft_strdup("Record_type=Hyper");
	length += ft_strlen(tag_value_pair);
	ft_enqueue(string_queue, (void *)tag_value_pair);
	*tags_set = ft_strcat_queue(string_queue, length);
	ft_queue_remove(&string_queue);
	return (length);
}

static size_t	influxdb_fields_add(
							const char **const field_set,
							const double learning_rate,
							const size_t percentage)
{
	t_queue				*string_queue;
	char				string_for_values[100];
	size_t				length;

	length = 0;
	string_queue = ft_queue_init();
	ft_sprintf(string_for_values, "learning_rate=%f", learning_rate);
	length += ft_strlen(string_for_values);
	ft_enqueue(string_queue, ft_strdup(string_for_values));
	length++;
	ft_enqueue(string_queue, ft_strdup(","));
	ft_sprintf(string_for_values, "percentage=%u", percentage);
	length += ft_strlen(string_for_values);
	ft_enqueue(string_queue, ft_strdup(string_for_values));
	*field_set = ft_strcat_queue(string_queue, length);
	ft_queue_remove(&string_queue);
	return (length);
}

void	send_hyper_params_to_database(
							const t_tcp_connection *const influxdb_connection,
							const t_hyper_params *const hyper_params)
{
	t_influxdb_line		influxdb_line;
	const char			*line;
	size_t				total_len;
	double				learning_rate;
	size_t				percentage;

	if (influxdb_connection)
	{
		learning_rate = hyper_params->learning_rate;
		percentage = hyper_params->dataset_split_order->extra_info;
		total_len = 0;
		total_len += influxdb_measurement(&influxdb_line.measurement,
				"dataset_train");
		total_len += influxdb_tags_add(&influxdb_line.tag_set);
		total_len += influxdb_fields_add(&influxdb_line.field_set, learning_rate, percentage);
		total_len += influxdb_timestamp_add(&influxdb_line.timestamp);
		line = elements_merge(&influxdb_line, total_len);
		influxdb_element_remove(&influxdb_line);
		ft_influxdb_write(influxdb_connection, line, NULL, 1);
		ft_strdel((char **)&line);
	}
	else
		FT_LOG_DEBUG("Cost value is not sent to influxdb");
	return ;
}
