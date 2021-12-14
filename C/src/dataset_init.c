/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:13:48 by juhani            #+#    #+#             */
/*   Updated: 2021/12/14 23:20:06 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	add_x_values_to_dataset(
					double *const *const dataset_table,
					const t_input_data *const input_data,
					const size_t col_id,
					const char *const *const record)
{
	size_t			row_id;
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

static void	add_y_values_to_dataset(
					double *const *const dataset_table,
					const size_t col_id,
					const char *const *const record)
{
	size_t			row_id;
	const char		*value_string;

	row_id = -1;
	value_string = record[1];
	if (ft_strequ(value_string, "B"))
		dataset_table[0][col_id] = 1;
	else
		dataset_table[1][col_id] = 1;
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
			add_x_values_to_dataset(dataset_train_table, input_data,
				col_id_train++, record);
		else
			add_x_values_to_dataset(dataset_test_table, input_data,
				col_id_test++, record);
	}
	return ;
}

static void	set_output_values_to_dataset(
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
			add_y_values_to_dataset(dataset_train_table,
				col_id_train++, record);
		else
			add_y_values_to_dataset(dataset_test_table,
				col_id_test++, record);
	}
	// y_matrix_row_names(&dataset->y->row_names);
	return ;
}

static void	set_values_to_dataset(
					const t_input_data *const input_data,
					t_dataset **dataset_array)
{
	set_input_values_to_dataset(input_data,
		(double *const *const)dataset_array[E_TRAIN]->x->table,
		(double *const *const)dataset_array[E_TEST]->x->table);
	set_output_values_to_dataset(input_data,
		(double *const *const)dataset_array[E_TRAIN]->y->table,
		(double *const *const)dataset_array[E_TEST]->y->table);
	return ;
}

t_dataset	**dataset_init(const t_input_data *const input_data)
{
	t_dataset		**dataset_array;
	size_t			i;

	dataset_array = ft_memalloc(sizeof(*dataset_array) * NUM_OF_DATASETS);
	i = -1;
	while (++i < NUM_OF_DATASETS)
		dataset_array[i] = ft_memalloc(sizeof(*dataset_array[i]));
	dataset_array[E_TRAIN]->x = ml_matrix_create(
			input_data->num_of_input_functions,
			input_data->num_of_records.train);
	dataset_array[E_TEST]->x = ml_matrix_create(
			input_data->num_of_input_functions,
			input_data->num_of_records.test);
	dataset_array[E_TRAIN]->y = ml_matrix_create(
			input_data->num_of_output_functions,
			input_data->num_of_records.train);
	dataset_array[E_TEST]->y = ml_matrix_create(
			input_data->num_of_output_functions,
			input_data->num_of_records.test);
	set_values_to_dataset(input_data, dataset_array);
	return (dataset_array);
}
