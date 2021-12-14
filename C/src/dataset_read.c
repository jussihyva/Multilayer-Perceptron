/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:00:14 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/14 13:06:45 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

// static void	select_functions_print(void)
// {
// 	size_t		i;

// 	if (ft_logging_level() <= LOG_DEBUG)
// 	{
// 		i = -1;
// 		while (++i < NUMBER_OF_COLUMNS)
// 		{
// 			if (g_dataset_file_x_columns[i])
// 				ft_printf(" %s", g_dataset_file_column_names[i]);
// 		}
// 		ft_printf("\n");
// 		ft_printf("\n");
// 		i = -1;
// 		while (++i < NUMBER_OF_COLUMNS)
// 		{
// 			if (g_dataset_file_y_columns[i])
// 				ft_printf(" %s", g_dataset_file_column_names[i]);
// 		}
// 		ft_printf("\n");
// 	}
// 	return ;
// }

// static void	y_matrix_row_names(t_name_array *row_names)
// {
// 	row_names->names = ft_memalloc(sizeof(*row_names->names) * 2);
// 	row_names->lengths = ft_memalloc(sizeof(*row_names->lengths) * 2);
// 	row_names->names[0] = ft_strdup("M");
// 	row_names->lengths[0] = ft_strlen(row_names->names[0]);
// 	row_names->names[1] = ft_strdup("B");
// 	row_names->lengths[1] = ft_strlen(row_names->names[1]);
// 	return ;
// }

// static void	x_matrix_row_names(t_name_array *row_names)
// {
// 	size_t			i;
// 	t_queue			*queue;

// 	queue = ft_queue_init();
// 	i = -1;
// 	while (++i < NUMBER_OF_COLUMNS)
// 	{
// 		if (g_dataset_file_x_columns[i])
// 			ft_enqueue(queue,
// 				(void *)ft_strdup(g_dataset_file_column_names[i]));
// 	}
// 	row_names->names = ft_memalloc(sizeof(*row_names->names) * queue->len);
// 	row_names->lengths = ft_memalloc(sizeof(*row_names->lengths) * queue->len);
// 	i = 0;
// 	while (!ft_is_queue_empty(queue))
// 	{
// 		row_names->names[i] = (const char *)ft_dequeue(queue);
// 		row_names->lengths[i] = ft_strlen(row_names->names[i]);
// 		i++;
// 	}
// 	ft_queue_remove(&queue);
// 	return ;
// }

// size_t	*get_valid_columns_and_create_matrix(
// 							const size_t rows,
// 							const t_bool *const array_of_valid_columns,
// 							t_dataset *const dataset)
// {
// 	size_t		num_of_columns;
// 	size_t		*valid_columns;
// 	size_t		i;
// 	size_t		j;

// 	num_of_columns = 0;
// 	i = -1;
// 	while (++i < NUMBER_OF_COLUMNS)
// 	{
// 		if (array_of_valid_columns[i])
// 			num_of_columns++;
// 	}
// 	valid_columns = ft_memalloc(sizeof(*valid_columns) * num_of_columns);
// 	i = -1;
// 	j = 0;
// 	while (++i < NUMBER_OF_COLUMNS)
// 	{
// 		if (array_of_valid_columns[i])
// 			valid_columns[j++] = i;
// 	}
// 	if (num_of_columns == 1)
// 		dataset->y = ml_matrix_create(num_of_columns + 1, rows);
// 	else
// 	{
// 		dataset->train = ml_matrix_create(num_of_columns * 0.7, rows);
// 		dataset->test = ml_matrix_create(
// 				num_of_columns - dataset->train->size.rows, rows);
// 	}
// 	return (valid_columns);
// }

// void	update_content_of_matrix_y(
// 							const char ***row_array,
// 							const size_t rows,
// 							t_dataset *const dataset)
// {
// 	size_t			i;
// 	const char		*value_string;
// 	size_t			*valid_columns;

// 	valid_columns = get_valid_columns_and_create_matrix(rows,
// 			g_dataset_file_y_columns, dataset);
// 	i = -1;
// 	while (++i < dataset->y->size.cols)
// 	{
// 		value_string = row_array[i][valid_columns[0]];
// 		if (ft_strequ(value_string, "B"))
// 			((double **)dataset->y->table)[0][i] = 1;
// 		else
// 			((double **)dataset->y->table)[1][i] = 1;
// 	}
// 	ft_memdel((void **)&valid_columns);
// 	y_matrix_row_names(&dataset->y->row_names);
// 	return ;
// }

static size_t	*calculate_num_of_input_functions(size_t *num_of_input_functions)
{
	size_t		i;
	size_t		j;
	size_t		*valid_input_columns;

	*num_of_input_functions = 0;
	i = -1;
	while (++i < NUMBER_OF_COLUMNS)
	{
		if (g_dataset_file_x_columns[i])
			(*num_of_input_functions)++;
	}
	valid_input_columns
		= ft_memalloc(sizeof(*valid_input_columns) * *num_of_input_functions);
	j = 0;
	i = -1;
	while (++i < NUMBER_OF_COLUMNS)
	{
		if (g_dataset_file_x_columns[i])
		{
			valid_input_columns[j] = i;
			j++;
		}
	}
	return (valid_input_columns);
}

static void	update_content_of_dataset(
						const size_t *const valid_input_columns,
						const size_t *const record_id_array,
						const char *const *const *input_records,
						const t_dataset *const dataset)
{
	t_size_2d		i;
	const char		*const *row;
	const char		*value_string;
	double			value;
	char			*endptr;
	double			*const *dataset_table;
	size_t			row_id;

	dataset_table = ((double **)dataset->x->table);
	i.rows = -1;
	row_id = 0;
	while (++i.rows < dataset->x->size.rows)
	{
		row = input_records[record_id_array[row_id]];
		i.cols = -1;
		while (++i.cols < dataset->x->size.cols)
		{
			value_string = row[valid_input_columns[i.cols]];
			errno = 0;
			value = strtod(value_string, &endptr);
			if (errno || *endptr != '\0' || value_string == endptr)
				ft_printf("Value is not valid\n");
			dataset_table[i.rows][i.cols] = value;
		}
		i.cols++;
		row_id++;
	}
	return ;
}

t_neural_network_input_data	*dataset_split_input_data_for_train_and_test(
							const char *const *const *const row_array,
							const size_t rows,
							t_dataset *const dataset_train,
							t_dataset *const dataset_test)
{
	t_neural_network_input_data		*neural_network_input_data;
	const size_t					*valid_input_columns;

	neural_network_input_data = ft_memalloc(sizeof(neural_network_input_data));
	neural_network_input_data->input_records = row_array;
	neural_network_input_data->num_of_records_for_train = rows * 0.7;
	neural_network_input_data->num_of_records_for_test
		= rows - neural_network_input_data->num_of_records_for_train;
	valid_input_columns = calculate_num_of_input_functions(
			&neural_network_input_data->num_of_input_functions);
	neural_network_input_data->num_of_output_functions = 2;
	dataset_train->x = ml_matrix_create(
			neural_network_input_data->num_of_input_functions,
			neural_network_input_data->num_of_records_for_train);
	dataset_test->x = ml_matrix_create(
			neural_network_input_data->num_of_input_functions,
			neural_network_input_data->num_of_records_for_test);
	dataset_train->y = ml_matrix_create(
			neural_network_input_data->num_of_output_functions,
			neural_network_input_data->num_of_records_for_train);
	dataset_test->y = ml_matrix_create(
			neural_network_input_data->num_of_output_functions,
			neural_network_input_data->num_of_records_for_test);
	update_content_of_dataset(valid_input_columns,
		neural_network_input_data->train_record_id_array,
		neural_network_input_data->input_records,
		dataset_train);
	return (neural_network_input_data);
}
