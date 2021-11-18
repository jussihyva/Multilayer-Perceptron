/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bias_weigth_values_set.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 12:58:48 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/18 16:15:32 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

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
	file_attr_remove(&file_attr);
	return ;
}
