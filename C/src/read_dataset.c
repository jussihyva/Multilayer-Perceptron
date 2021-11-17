/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dataset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:00:14 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/17 12:02:47 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static t_matrix	*update_content_of_matrix(
							const char ***row_array,
							size_t *valid_columns,
							t_matrix *matrix)
{
	t_size_2d		i;
	const char		*value_string;
	double			value;
	char			*endptr;

	i.cols = -1;
	while (++i.cols < matrix->size.cols)
	{
		i.rows = -1;
		while (++i.rows < matrix->size.rows)
		{
			value_string = row_array[i.cols][valid_columns[i.rows]];
			errno = 0;
			value = strtod(value_string, &endptr);
			if (errno || *endptr != '\0' || value_string == endptr)
				ft_printf("Value is not valid\n");
			((double **)matrix->table)[i.rows][i.cols] = value;
		}
	}
	return (matrix);
}

static size_t	*get_valid_columns_and_create_matrix(
							const size_t rows,
							const t_bool *const array_of_valid_columns,
							t_matrix **matrix)
{
	size_t		num_of_columns;
	size_t		*valid_columns;
	size_t		i;
	size_t		j;

	num_of_columns = 0;
	i = -1;
	while (++i < NUMBER_OF_COLUMNS)
	{
		if (array_of_valid_columns[i])
			num_of_columns++;
	}
	valid_columns = ft_memalloc(sizeof(*valid_columns) * num_of_columns);
	i = -1;
	j = 0;
	while (++i < NUMBER_OF_COLUMNS)
	{
		if (array_of_valid_columns[i])
		{
			valid_columns[j] = i;
			j++;
		}
	}
	*matrix = ml_matrix_create(num_of_columns, rows);
	return (valid_columns);
}

static size_t	*get_valid_columns_and_create_matrix_y(
							const size_t rows,
							const t_bool *const array_of_valid_columns,
							t_matrix **matrix)
{
	size_t		num_of_columns;
	size_t		*valid_columns;
	size_t		i;
	size_t		j;

	num_of_columns = 0;
	i = -1;
	while (++i < NUMBER_OF_COLUMNS)
	{
		if (array_of_valid_columns[i])
			num_of_columns++;
	}
	valid_columns = ft_memalloc(sizeof(*valid_columns) * num_of_columns);
	i = -1;
	j = 0;
	while (++i < NUMBER_OF_COLUMNS)
	{
		if (array_of_valid_columns[i])
		{
			valid_columns[j] = i;
			j++;
		}
	}
	*matrix = ml_matrix_create(num_of_columns + 1, rows);
	return (valid_columns);
}

static t_matrix	*update_content_of_matrix_y(
							const char ***row_array,
							const size_t rows,
							t_matrix **matrix)
{
	size_t			i;
	const char		*value_string;
	size_t			*valid_columns;

	valid_columns = get_valid_columns_and_create_matrix_y(rows,
			g_dataset_file_y_columns, matrix);
	i = -1;
	while (++i < (*matrix)->size.cols)
	{
		value_string = row_array[i][valid_columns[0]];
		if (ft_strequ(value_string, "B"))
			((double **)(*matrix)->table)[0][i] = 1;
		else
			((double **)(*matrix)->table)[1][i] = 1;
	}
	ft_memdel((void **)&valid_columns);
	return (*matrix);
}

static void	select_functions_print(void)
{
	size_t		i;

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
	return ;
}

t_dataset	*read_dataset(const char *const file_path)
{
	t_file_attr		*file_attr;
	t_dataset		*dataset;
	size_t			*valid_columns;

	file_attr = ft_read_file(file_path, E_CSV);
	if (!file_attr || file_attr->read_failure)
	{
		dataset = NULL;
		FT_LOG_ERROR("Reading of file %s failed!", file_path);
	}
	else
	{
		dataset = ft_memalloc(sizeof(*dataset));
		valid_columns = get_valid_columns_and_create_matrix(file_attr->rows,
				g_dataset_file_x_columns, &dataset->x);
		update_content_of_matrix(file_attr->row_array, valid_columns,
			dataset->x);
		ft_memdel((void **)&valid_columns);
		update_content_of_matrix_y(file_attr->row_array, file_attr->rows,
			&dataset->y);
		select_functions_print();
	}
	file_attr_remove(&file_attr);
	return (dataset);
}
