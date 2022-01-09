/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:37:31 by juhani            #+#    #+#             */
/*   Updated: 2022/01/09 11:15:42 by jkauppi          ###   ########.fr       */
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

static t_split_mode	set_mode(const char mode_char)
{
	t_split_mode	split_mode;

	split_mode = 0;
	if (mode_char == 'B')
		split_mode = E_BEGIN;
	else if (mode_char == 'E')
		split_mode = E_END;
	else if (mode_char == 'R')
		split_mode = E_RAND;
	else
		FT_LOG_ERROR("Split mode %c is not supported.", mode_char);
	return (split_mode);
}

const t_split_order	*set_split_mode(
						const t_argc_argv *const argc_argv,
						t_split_order *const split_order)
{
	const char			*arg;
	char				*endptr;
	char				mode_char;

	arg = argc_argv->argv[argc_argv->i];
	mode_char = *arg;
	arg++;
	split_order->split_mode = set_mode(mode_char);
	errno = 0;
	split_order->extra_info = strtoul(arg, &endptr, 10);
	if (errno != 0 || *endptr != '\0')
		FT_LOG_ERROR("Value of param -s is not valid");
	else if (split_order->extra_info > 100)
		FT_LOG_ERROR("Maximum value for split mode (-s) is 100");
	return (split_order);
}

size_t	set_num_of_epochs(const t_argc_argv *const argc_argv)
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

size_t	set_num_of_layers(const t_argc_argv *const argc_argv)
{
	const char		*arg;
	char			*endptr;
	size_t			num_of_layers;

	errno = 0;
	arg = argc_argv->argv[argc_argv->i];
	num_of_layers = ft_strtoi(arg, &endptr, 10);
	if (errno != 0 || *endptr != '\0')
		FT_LOG_ERROR("Value of param -E is not valid");
	if (num_of_layers > 5)
		FT_LOG_ERROR("Maximum number of layers (-M) is 5");
	if (num_of_layers < 2)
		FT_LOG_ERROR("Minimum number of layers (-M) is 2");
	return (num_of_layers);
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
	t_influxdb_elem		influxdb_elem;
	char				*line;
	size_t				len;
	double				learning_rate;
	size_t				percentage;

	if (influxdb_connection)
	{
		learning_rate = hyper_params->learning_rate;
		percentage = hyper_params->split_order.extra_info;
		len = 0;
		len += influxdb_measurement(&influxdb_elem.measurement,
				"dataset_train");
		len += influxdb_tags_add(&influxdb_elem.tag_set);
		len += influxdb_fields_add(&influxdb_elem.field_set,
				learning_rate, percentage);
		len += influxdb_timestamp_set(&influxdb_elem.timestamp);
		line = ft_strdup("");
		influxdb_line_extend(&influxdb_elem, len, &line);
		influxdb_elem_remove(&influxdb_elem);
		ft_influxdb_write(influxdb_connection, line, NULL, 1);
		ft_strdel((char **)&line);
	}
	else
		FT_LOG_DEBUG("Cost value is not sent to influxdb");
	return ;
}
