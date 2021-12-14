/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:00:14 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/14 16:55:39 by jkauppi          ###   ########.fr       */
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

static size_t	*calculate_num_of_input_functions(
									size_t *const num_of_input_functions)
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

static void	add_record_values_to_dataset(
					double *const *const dataset_table,
					const t_input_data *const input_data,
					const size_t col_id,
					const char *const *const record)
{
	size_t		row_id;
	const char		*value_string;
	double			value;
	char			*endptr;

	row_id = -1;
	while (++row_id < input_data->num_of_input_functions)
	{
		value_string = record[input_data->valid_input_column_ids[row_id]];
		errno = 0;
		value = strtod(value_string, &endptr);
		if (errno || *endptr != '\0' || value_string == endptr)
			ft_printf("Value is not valid\n");
		dataset_table[row_id][col_id] = value;
	}
	return ;
}
static void	set_input_values_to_dataset(
						const t_input_data *const input_data,
						double *const *const dataset_train_table,
						double *const *const dataset_test_table)
{
	size_t			col_id_train;
	size_t			col_id_test;
	const char		*const *record;
	size_t			record_id;

	col_id_train = 0;
	col_id_test = 0;
	record_id = -1;
	while (++record_id < input_data->num_of_records.total)
	{
		record = input_data->input_record_array[record_id];
		if (input_data->dataset_type_array[record_id] == E_TRAIN)
			add_record_values_to_dataset(dataset_train_table, input_data,
				col_id_train++, record);
		else
			add_record_values_to_dataset(dataset_test_table, input_data,
				col_id_test++, record);
	}
	return ;
}

static const t_dataset_type	*decide_records_to_datasets(
								t_num_of_records *const num_of_records)
{
	t_dataset_type	*dataset_type_array;
	size_t			i;

	dataset_type_array
		= ft_memalloc(sizeof(*dataset_type_array) * num_of_records->total);
	num_of_records->train = num_of_records->total * 0.7;
	num_of_records->test = num_of_records->total - num_of_records->train;
	i = -1;
	while (++i < num_of_records->total)
	{
		if (i < num_of_records->train)
			dataset_type_array[i] = E_TRAIN;
		else
			dataset_type_array[i] = E_TEST;
	}
	return (dataset_type_array);
}

t_input_data	*dataset_split_input_data_for_train_and_test(
							const char *const *const *const row_array,
							const size_t rows,
							t_dataset *const dataset_train,
							t_dataset *const dataset_test)
{
	t_input_data	*input_data;

	input_data = ft_memalloc(sizeof(input_data));
	input_data->num_of_records.total = rows;
	input_data->input_record_array = row_array;
	input_data->valid_input_column_ids = calculate_num_of_input_functions(
			&input_data->num_of_input_functions);
	input_data->num_of_output_functions = 2;
	input_data->dataset_type_array
		= decide_records_to_datasets(&input_data->num_of_records);
	dataset_train->x = ml_matrix_create(
			input_data->num_of_input_functions,
			input_data->num_of_records.train);
	dataset_test->x = ml_matrix_create(
			input_data->num_of_input_functions,
			input_data->num_of_records.test);
	dataset_train->y = ml_matrix_create(
			input_data->num_of_output_functions,
			input_data->num_of_records.train);
	dataset_test->y = ml_matrix_create(
			input_data->num_of_output_functions,
			input_data->num_of_records.test);
	set_input_values_to_dataset(input_data,
		(double *const *const)dataset_train->x->table,
		(double *const *const)dataset_test->x->table);
	return (input_data);
}
