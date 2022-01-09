/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 19:16:19 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/09 11:41:34 by jkauppi          ###   ########.fr       */
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

static char	*influxdb_elements_merge(
							const t_influxdb_elem *const influxdb_elem,
							size_t len)
{
	char		*line;
	size_t		actual_len;
	size_t		additional_spaces;
	size_t		additional_new_line;

	additional_spaces = 2;
	additional_new_line = 1;
	len += additional_spaces + additional_new_line;
	line = ft_strnew(sizeof(*line) * len);
	actual_len = ft_sprintf(line, "%s%s %s %s\n",
			influxdb_elem->measurement,
			influxdb_elem->tag_set,
			influxdb_elem->field_set,
			influxdb_elem->timestamp);
	if (actual_len != len)
		FT_LOG_WARN("Influxdb line: %lu <--> %lu", actual_len, len);
	return (line);
}

void	influxdb_line_extend(
						const t_influxdb_elem *const influxdb_elem,
						size_t len,
						char **const line)
{
	char	*original_line;
	char	*extended_line;

	original_line = *line;
	extended_line = influxdb_elements_merge(influxdb_elem, len);
	*line = ft_strjoin(original_line, extended_line);
	ft_strdel(&original_line);
	ft_strdel(&extended_line);
	return ;
}
