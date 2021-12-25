/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_softmax_result_to_database.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:33:42 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/25 14:35:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static size_t	influxdb_tags_add(
							const char **const tag_set,
							const char *const example_id)
{
	t_queue			*string_queue;
	const char		*tag_value_pair;
	size_t			length;

	string_queue = ft_queue_init();
	length = 0;
	length++;
	ft_enqueue(string_queue, ft_strdup(","));
	tag_value_pair = ft_strdup("Record_type=Softmax");
	length += ft_strlen(tag_value_pair);
	ft_enqueue(string_queue, (void *)tag_value_pair);
	length++;
	ft_enqueue(string_queue, ft_strdup(","));
	tag_value_pair = ft_strjoin("ExampleId=", example_id);
	length += ft_strlen(tag_value_pair);
	ft_enqueue(string_queue, (void *)tag_value_pair);
	*tag_set = ft_strcat_queue(string_queue, length);
	ft_queue_remove(&string_queue);
	return (length);
}

static size_t	influxdb_fields_add(
							const char **const field_set,
							const t_matrix *matrix,
							const size_t col)
{
	t_queue			*string_queue;
	size_t			i;
	char			string[100];
	double			value;
	double			bigger_value;
	size_t			length;

	length = 0;
	string_queue = ft_queue_init();
	ft_sprintf(string, "ExampleId=%u", col);
	length += ft_strlen(string);
	ft_enqueue(string_queue, ft_strdup(string));
	bigger_value = DBL_MIN;
	i = -1;
	while (++i < matrix->size.rows)
	{
		length++;
		ft_enqueue(string_queue, ft_strdup(","));
		ft_sprintf(string, "%d", i);
		length += ft_strlen(string);
		ft_enqueue(string_queue, ft_strdup(string));
		length++;
		ft_enqueue(string_queue, ft_strdup("="));
		value = ((double **)matrix->table)[i][col];
		bigger_value = ft_max_double(bigger_value, value);
		ft_sprintf(string, "%f", value);
		length += ft_strlen(string);
		ft_enqueue(string_queue, ft_strdup(string));
	}
	length++;
	ft_enqueue(string_queue, ft_strdup(","));
	ft_sprintf(string, "BiggerValue=%f", bigger_value);
	length += ft_strlen(string);
	ft_enqueue(string_queue, ft_strdup(string));
	*field_set = ft_strcat_queue(string_queue, length);
	ft_queue_remove(&string_queue);
	return (length);
}

void	send_softmax_result_to_database(
							const t_grad_descent_attr *const grad_descent_attr)
{
	t_influxdb_line		influxdb_line;
	const char			*line;
	const char			*example_id;
	size_t				total_len;
	t_size_2d			i;

	if (grad_descent_attr->influxdb_connection)
	{
		i.cols = -1;
		while (++i.cols < grad_descent_attr->softmax->size.cols)
		{
			total_len = 0;
			total_len += influxdb_measurement(&influxdb_line.measurement,
					"dataset_train");
			example_id = ft_itoa(i.cols);
			total_len += influxdb_tags_add(&influxdb_line.tag_set, example_id);
			ft_strdel((char **)&example_id);
			total_len += influxdb_fields_add(&influxdb_line.field_set,
					grad_descent_attr->softmax, i.cols);
			total_len += influxdb_timestamp_add(&influxdb_line.timestamp);
			line = elements_merge(&influxdb_line, total_len);
			influxdb_element_remove(&influxdb_line);
			ft_influxdb_write(grad_descent_attr->influxdb_connection,
				line, NULL, 1);
			ft_strdel((char **)&line);
		}
	}
	else
		FT_LOG_DEBUG("Cost value is not sent to influxdb");
	return ;
}
