/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_softmax_result_to_database.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:33:42 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/25 10:21:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static size_t	add_exampleid(
						const size_t example_id,
						const char *const special_chars,
						t_queue *const key_value_queue)
{
	t_key_value_pair	key_value_pair;
	char				*key_value_string;
	size_t				length;

	length = 0;
	key_value_pair.key = "ExampleId";
	key_value_pair.key_type = E_STRING;
	key_value_pair.value = (void *)&example_id;
	key_value_pair.value_type = E_SIZE_T;
	length += influxdb_key_value_pair_string_create(&key_value_pair,
			special_chars, &key_value_string);
	ft_enqueue(key_value_queue, (void *)key_value_string);
	return (length);
}

static size_t	add_bigger_value(
						const double bigger_value,
						const char *const special_chars,
						t_queue *const key_value_queue)
{
	t_key_value_pair	key_value_pair;
	char				*key_value_string;
	size_t				length;

	length = 0;
	key_value_pair.key = "BiggerValue";
	key_value_pair.key_type = E_STRING;
	key_value_pair.value = (void *)&bigger_value;
	key_value_pair.value_type = E_DOUBLE;
	length += influxdb_key_value_pair_string_create(&key_value_pair,
			special_chars, &key_value_string);
	ft_enqueue(key_value_queue, (void *)key_value_string);
	return (length);
}

static size_t	get_softmax_key_value_pairs(
						const t_matrix *const softmax,
						const size_t col_id,
						const char *const special_chars,
						t_queue *const key_value_queue)
{
	size_t				length;
	size_t				row_id;
	char				*key_value_string;
	t_key_value_pair	key_value_pair;
	double				bigger_value;

	bigger_value = DBL_MIN;
	length = 0;
	key_value_pair.key_type = E_SIZE_T;
	key_value_pair.value_type = E_DOUBLE;
	row_id = -1;
	while (++row_id < softmax->size.rows)
	{
		key_value_pair.key = (void *)&row_id;
		key_value_pair.value
			= (void *)&((double **)softmax->table)[row_id][col_id];
		bigger_value = ft_max_double(bigger_value,
				*(double *)key_value_pair.value);
		length += influxdb_key_value_pair_string_create(&key_value_pair,
				special_chars, &key_value_string);
		ft_enqueue(key_value_queue, (void *)key_value_string);
	}
	length += add_bigger_value(bigger_value, special_chars, key_value_queue);
	return (length);
}

static size_t	influxdb_elem_create(
						t_influxdb_elem *influxdb_elem,
						t_queue *key_value_queue,
						const t_matrix *const softmax,
						const size_t col_id)
{
	size_t				len;

	len = 0;
	influxdb_elem->measurement = ft_strdup("");
	get_measurement_value("dataset_train", key_value_queue);
	add_record_type("Softmax", SPECIAL_CHARS_INFLUXDB_TAGS, key_value_queue);
	add_exampleid(col_id, SPECIAL_CHARS_INFLUXDB_TAGS, key_value_queue);
	len += influxdb_elem_string_create(&influxdb_elem->tag_set,
			key_value_queue);
	add_exampleid(col_id, SPECIAL_CHARS_INFLUXDB_TAGS, key_value_queue);
	get_softmax_key_value_pairs(softmax, col_id, SPECIAL_CHARS_INFLUXDB_FIELDS,
		key_value_queue);
	len += influxdb_elem_string_create(&influxdb_elem->field_set,
			key_value_queue);
	len += influxdb_timestamp_set(&influxdb_elem->timestamp);
	return (len);
}

void	send_softmax_result_to_database(
					const t_tcp_connection *const influxdb_connection,
					t_queue *const key_value_queue,
					const t_matrix *const softmax,
					const size_t example_id)
{
	t_influxdb_elem		influxdb_elem;
	char				*line;
	size_t				len;

	len = influxdb_elem_create(&influxdb_elem, key_value_queue, softmax,
			example_id);
	line = ft_strdup("");
	influxdb_line_extend(&influxdb_elem, len, &line);
	influxdb_elem_remove(&influxdb_elem);
	ft_influxdb_write(influxdb_connection, line, NULL, 1);
	ft_strdel((char **)&line);
	return ;
}
