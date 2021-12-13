/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:00:14 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/13 15:23:05 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static const char	*g_dataset_file_column_names[NUMBER_OF_COLUMNS]
	= {"ID number", "Diagnosis", "Mean Radius", "Mean Texture",
	"Mean Perimeter", "Mean Area", "Mean Smoothness",
	"Mean Compactness", "Mean Concavity", "Mean Concave points",
	"Mean Symmetry", "Mean Fractal dimension", "Radius SE",
	"Texture SE", "Perimeter SE", "Area SE", "Smoothness SE",
	"Compactness SE", "Concavity SE", "Concave points SE",
	"Symmetry SE", "Fractal dimension SE", "Worst Radius",
	"Worst Texture", "Worst Perimeter", "Worst Area",
	"Worst Smoothness", "Worst Compactness", "Worst Concavity",
	"Worst Concave points", "Worst Symmetry",
	"Worst Fractal dimension"};

static void	select_functions_print(void)
{
	size_t		i;

	if (ft_logging_level() <= LOG_DEBUG)
	{
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
	}
	return ;
}

static void	y_matrix_row_names(t_name_array *row_names)
{
	row_names->names = ft_memalloc(sizeof(*row_names->names) * 2);
	row_names->lengths = ft_memalloc(sizeof(*row_names->lengths) * 2);
	row_names->names[0] = ft_strdup("M");
	row_names->lengths[0] = ft_strlen(row_names->names[0]);
	row_names->names[1] = ft_strdup("B");
	row_names->lengths[1] = ft_strlen(row_names->names[1]);
	return ;
}

static void	x_matrix_row_names(t_name_array *row_names)
{
	size_t			i;
	t_queue			*queue;

	queue = ft_queue_init();
	i = -1;
	while (++i < NUMBER_OF_COLUMNS)
	{
		if (g_dataset_file_x_columns[i])
			ft_enqueue(queue,
				(void *)ft_strdup(g_dataset_file_column_names[i]));
	}
	row_names->names = ft_memalloc(sizeof(*row_names->names) * queue->len);
	row_names->lengths = ft_memalloc(sizeof(*row_names->lengths) * queue->len);
	i = 0;
	while (!ft_is_queue_empty(queue))
	{
		row_names->names[i] = (const char *)ft_dequeue(queue);
		row_names->lengths[i] = ft_strlen(row_names->names[i]);
		i++;
	}
	ft_queue_remove(&queue);
	return ;
}

void	update_content_of_matrix(
						const t_file_attr *const file_attr,
						const size_t *const valid_columns,
						t_dataset *const dataset)
{
	t_size_2d		i;
	const char		*value_string;
	double			value;
	char			*endptr;
	size_t			row_id;
	size_t			num_of_examples_train;
	size_t			num_of_examples_test;
	const char		*const *row;

	num_of_examples_train = dataset->train->size.rows;
	num_of_examples_test = dataset->test->size.rows;
	row_id = 0;
	i.cols = 0;
	while (num_of_examples_train--)
	{
		row = file_attr->row_array[row_id];
		i.rows = -1;
		while (++i.rows < dataset->train->size.rows)
		{
			value_string = row[valid_columns[i.rows]];
			errno = 0;
			value = strtod(value_string, &endptr);
			if (errno || *endptr != '\0' || value_string == endptr)
				ft_printf("Value is not valid\n");
			((double **)dataset->train->table)[i.rows][i.cols] = value;
		}
		i.cols++;
		row_id++;
	}
	i.cols = 0;
	while (num_of_examples_test--)
	{
		row = file_attr->row_array[row_id];
		i.rows = -1;
		while (++i.rows < dataset->test->size.rows)
		{
			value_string = row[valid_columns[i.rows]];
			errno = 0;
			value = strtod(value_string, &endptr);
			if (errno || *endptr != '\0' || value_string == endptr)
				ft_printf("Value is not valid\n");
			((double **)dataset->test->table)[i.rows][i.cols] = value;
		}
		i.cols++;
		row_id++;
	}
	x_matrix_row_names(&dataset->train->row_names);
	x_matrix_row_names(&dataset->test->row_names);
	select_functions_print();
	return ;
}

size_t	*get_valid_columns_and_create_matrix(
							const size_t rows,
							const t_bool *const array_of_valid_columns,
							t_dataset *const dataset)
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
			valid_columns[j++] = i;
	}
	if (num_of_columns == 1)
		dataset->y = ml_matrix_create(num_of_columns + 1, rows);
	else
	{
		dataset->train = ml_matrix_create(num_of_columns * 0.7, rows);
		dataset->test = ml_matrix_create(
				num_of_columns - dataset->train->size.rows, rows);
	}
	return (valid_columns);
}

void	update_content_of_matrix_y(
							const char ***row_array,
							const size_t rows,
							t_dataset *const dataset)
{
	size_t			i;
	const char		*value_string;
	size_t			*valid_columns;

	valid_columns = get_valid_columns_and_create_matrix(rows,
			g_dataset_file_y_columns, dataset);
	i = -1;
	while (++i < dataset->y->size.cols)
	{
		value_string = row_array[i][valid_columns[0]];
		if (ft_strequ(value_string, "B"))
			((double **)dataset->y->table)[0][i] = 1;
		else
			((double **)dataset->y->table)[1][i] = 1;
	}
	ft_memdel((void **)&valid_columns);
	y_matrix_row_names(&dataset->y->row_names);
	return ;
}
