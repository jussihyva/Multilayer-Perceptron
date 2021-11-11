/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dataset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:00:14 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/12 00:07:49 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "training.h"

static t_matrix	*create_x_matrix(const size_t rows, const char ***row_array)
{
	t_matrix	*matrix;
	size_t		num_of_columns;
	size_t		i;

	(void)row_array;
	num_of_columns = 0;
	i = -1;
	while (++i < NUMBER_OF_COLUMNS)
	{
		if (g_dataset_file_x_columns[i])
			num_of_columns++;
	}
	matrix = ml_matrix_create(num_of_columns, rows);
	return (matrix);
}

static t_matrix	*create_y_matrix(const size_t rows, const char ***row_array)
{
	t_matrix	*matrix;
	size_t		num_of_columns;
	t_size_2d	i;
	size_t		*index_array;
	t_list		*y_variant_lst;
	const char	*value;

	y_variant_lst = NULL;
	num_of_columns = 0;
	i.cols = -1;
	while (++i.cols < NUMBER_OF_COLUMNS)
	{
		if (g_dataset_file_y_columns[i.cols])
			num_of_columns++;
	}
	index_array = ft_memalloc(sizeof(*index_array) * num_of_columns);
	i.rows = -1;
	while (++i.rows < NUMBER_OF_COLUMNS)
	{
		i.cols = -1;
		while (++i.cols < num_of_columns)
		{
			value = row_array[i.rows][index_array[i.cols]];
		}
	}
	matrix = ml_matrix_create(num_of_columns, rows);
	return (matrix);
}


t_dataset	*read_dataset(const char *const file_path)
{
	t_file_attributes	*file_attributes;
	size_t				i;
	t_dataset			*dataset;

	dataset = ft_memalloc(sizeof(*dataset));
	file_attributes = ft_read_file(file_path, E_CSV);
	ft_strarray_print(file_attributes->row_array[0]);
	dataset->x = create_x_matrix(file_attributes->rows, file_attributes->row_array);
	dataset->y = create_y_matrix(file_attributes->rows, file_attributes->row_array);
	i = -1;
	while (++i < NUMBER_OF_COLUMNS)
	{
		if (g_dataset_file_x_columns[i])
			ft_printf(" %s", g_dataset_file_column_names[i]);
	}
	ft_printf("\n");
	ft_printf("\n");
	i = -1;
	while (++i < NUMBER_OF_COLUMNS)
	{
		if (g_dataset_file_y_columns[i])
			ft_printf(" %s", g_dataset_file_column_names[i]);
	}
	ft_printf("\n");
	file_attributes_remove(&file_attributes);
	return (dataset);
}