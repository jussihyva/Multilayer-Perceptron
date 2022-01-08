/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 19:16:19 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/08 19:25:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

// const char	*influxdb_line_create(void)
// {
// 	t_influxdb_line		influxdb_line;
// 	const char			*line;
// 	size_t				total_len;

// 	total_len = influxdb_measurement(&influxdb_line.measurement,
// 			"dataset_train");
// 	total_len += influxdb_tags_add(&influxdb_line.tag_set, i);
// 	total_len += influxdb_fields_add(&influxdb_line.field_set, iter_cnt,
// 			layer_output->cost[i]);
// 	total_len += influxdb_timestamp_add(&influxdb_line.timestamp);
// 	line = elements_merge(&influxdb_line, total_len);
// 	return (line);
// }
