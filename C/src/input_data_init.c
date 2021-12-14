/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_data_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:38:48 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/14 19:29:04 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

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

t_input_data	*input_data_init(
							const char *const *const *const row_array,
							const size_t rows)
{
	t_input_data	*input_data;

	input_data = ft_memalloc(sizeof(*input_data));
	input_data->num_of_records.total = rows;
	input_data->input_record_array = row_array;
	input_data->valid_input_column_ids = calculate_num_of_input_functions(
			&input_data->num_of_input_functions);
	input_data->num_of_output_functions = 2;
	input_data->dataset_type_array
		= decide_records_to_datasets(&input_data->num_of_records);
	input_data->dataset_array = dataset_init(input_data);
	return (input_data);
}
