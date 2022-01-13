/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:39:54 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/13 10:38:52 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static size_t	conv_to_string(
					const void *value,
					const t_data_type data_type,
					const char *const special_chars,
					char **const string)
{
	char		prel_string[100];
	size_t		len;

	len = 0;
	if (data_type == E_DOUBLE)
		len = ft_sprintf(prel_string, "%f", *(double *)value);
	else if (data_type == E_STRING)
		len = ft_sprintf(prel_string, "%s", (char *)value);
	else if (data_type == E_SIZE_T)
		len = ft_sprintf(prel_string, "%lu", *(size_t *)value);
	else
		FT_LOG_FATAL("Unkonwn key type: %d", data_type);
	*string = influxdb_special_chars_conv(special_chars, prel_string);
	return (len);
}

size_t	get_measurement_value(
					const char *const measurement,
					t_queue *const queue)
{
	size_t				length;
	char				*string;

	length = conv_to_string((void *)measurement, E_STRING,
			SPECIAL_CHARS_INFLUXDB_MEASUREMENT, &string);
	ft_enqueue(queue, (void *)string);
	return (length);
}

size_t	influxdb_key_value_pair_string_create(
						const t_key_value_pair *const key_value_pair,
						const char *const special_chars,
						char **const string)
{
	char		*key_string;
	char		*value_string;
	size_t		len;

	len = 0;
	len += conv_to_string(key_value_pair->key, key_value_pair->key_type,
			special_chars, &key_string);
	len += 1;
	len += conv_to_string(key_value_pair->value, key_value_pair->value_type,
			special_chars, &value_string);
	*string = ft_memalloc(sizeof(*string) * len);
	ft_strcat(*string, key_string);
	ft_strdel(&key_string);
	ft_strcat(*string, "=");
	ft_strcat(*string, value_string);
	ft_strdel(&value_string);
	return (len);
}

size_t	influxdb_elem_string_create(
							char **const elem_string,
							t_queue *key_value_queue)
{
	size_t				length;
	size_t				i;
	char				*key_value_string;

	i = -1;
	*elem_string = ft_strdup("");
	while (!ft_is_queue_empty(key_value_queue))
	{
		if ((*elem_string)[0] != '\0')
			ft_strext(elem_string, ",");
		key_value_string = ft_dequeue(key_value_queue);
		ft_strext(elem_string, key_value_string);
		ft_strdel(&key_value_string);
	}
	ft_strext(elem_string, " ");
	length = ft_strlen(*elem_string);
	return (length);
}

size_t	influxdb_timestamp_set(const char **const timestamp)
{
	size_t		utc_time_ms;
	char		string[100];
	size_t		length;

	utc_time_ms = ft_gettime();
	length = ft_sprintf(string, "%lu", utc_time_ms);
	*timestamp = ft_strdup(string);
	return (length);
}
