/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bias_weigth_values_set.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 12:58:48 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/18 14:00:08 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

// static void	parse_weight_bias_values(
// 							const char *const line,
// 							const size_t line_nbr,
// 							double *const weight_row,
// 							double *bias_value)
// {
// 	const char		**param_value;
// 	char			*endptr;
// 	size_t			num_of_values;
// 	size_t			i;

// 	param_value = ft_strsplit_ex(line, ':', &num_of_values, E_FALSE);
// 	if (num_of_values != (NUMBER_OF_HOGWARTS_COURSES + 1))
// 		FT_LOG_ERROR("Content of the file %s (line=%lu) is not valid!",
// 			"WEIGHT_BIAS_FILE_NAME", line_nbr);
// 	else
// 	{
// 		i = -1;
// 		while (++i < (NUMBER_OF_HOGWARTS_COURSES + 1))
// 		{
// 			errno = 0;
// 			if (i == 0)
// 				*bias_value = strtod(param_value[i], &endptr);
// 			else
// 				weight_row[i - 1] = strtod(param_value[i], &endptr);
// 			if (errno != 0 || *endptr != '\0')
// 				FT_LOG_ERROR("Content of the file %s (line=%lu) is not valid!",
// 					"WEIGHT_BIAS_FILE_NAME", line_nbr);
// 		}
// 	}
// 	ft_strarraydel(&param_value);
// }

// static void	read_weight_bias_values(
// 								const char *const weight_bias_file_yaml,
// 								const int fd,
// 								const t_matrix *const weight,
// 								const t_vector *const bias)
// {
// 	char		*line;
// 	size_t		i;

// 	(void)weight;
// 	line = NULL;
// 	i = 0;
// 	while (ft_get_next_line(fd, &line) > 0)
// 	{
// 		if (i >= bias->size)
// 			FT_LOG_ERROR("%s file includes unexpected number of lines!",
// 				weight_bias_file_yaml);
// 		// parse_weight_bias_values(line, i + 1, ((double **)weight->table)[i],
// 			// &((double *)bias->data)[i]);
// 		FT_LOG_DEBUG("%s", line);
// 		ft_strdel(&line);
// 		i++;
// 	}
// 	ft_strdel(&line);
// 	return ;
// }

void	bias_weigth_values_set(
						const t_vector *const bias,
						const t_matrix *const weight,
						const char *const weight_bias_file)
{
	t_file_attr		*file_attr;
	t_size_2d		i;
	char			*endptr;
	double			value;

	(void)weight;
	endptr = NULL;
	file_attr = ft_read_file(weight_bias_file, E_CSV);
	i.rows = -1;
	while (++i.rows < file_attr->rows)
	{
		i.cols = 0;
		value = strtod(file_attr->row_array[i.rows][i.cols], &endptr);
		((double *)bias->data)[i.rows] = value;
		while (file_attr->row_array[i.rows][++i.cols])
		{
			value = strtod(file_attr->row_array[i.rows][i.cols], &endptr);
			((double **)weight->table)[i.rows][i.cols - 1] = value;
			if (ft_logging_level() <= LOG_INFO)
				ft_printf("  %s", file_attr->row_array[i.rows][i.cols]);
		}
		if (ft_logging_level() <= LOG_INFO)
			ft_printf("\n");
	}
	return ;
}
