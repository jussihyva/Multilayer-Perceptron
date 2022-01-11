/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_tags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:14:51 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/11 12:15:51 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

size_t	add_record_type(
				const char *const record_type,
				const char *const special_chars,
				t_queue *const key_value_queue)
{
	size_t				length;
	t_key_value_pair	key_value_pair;
	char				*key_value_string;

	length = 0;
	key_value_pair.key = "Record_type";
	key_value_pair.key_type = E_STRING;
	key_value_pair.value = (void *)record_type;
	key_value_pair.value_type = E_STRING;
	length += influxdb_key_value_pair_string_create(&key_value_pair,
			special_chars, &key_value_string);
	ft_enqueue(key_value_queue, (void *)key_value_string);
	return (length);
}
