/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 12:25:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/16 12:34:57 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static t_dataset_type	*split_with_mode_begin(
								const t_num_of_records *const num_of_records)
{
	t_dataset_type	*dataset_type_array;
	size_t			i;

	dataset_type_array
		= ft_memalloc(sizeof(*dataset_type_array) * num_of_records->total);
	i = -1;
	while (++i < num_of_records->total)
	{
		{
			if (i < num_of_records->train)
				dataset_type_array[i] = E_TRAIN;
			else
				dataset_type_array[i] = E_TEST;
		}
	}
	return (dataset_type_array);
}

static t_dataset_type	*split_with_mode_end(
								const t_num_of_records *const num_of_records)
{
	t_dataset_type	*dataset_type_array;
	size_t			i;

	dataset_type_array
		= ft_memalloc(sizeof(*dataset_type_array) * num_of_records->total);
	i = -1;
	while (++i < num_of_records->total)
	{
		{
			if (i < num_of_records->test)
				dataset_type_array[i] = E_TEST;
			else
				dataset_type_array[i] = E_TRAIN;
		}
	}
	return (dataset_type_array);
}

t_dataset_type	*dataset_split(
						t_num_of_records *const num_of_records,
						const t_dataset_split_order *dataset_split_order)
{
	t_dataset_type	*dataset_type_array;

	num_of_records->train
		= num_of_records->total * dataset_split_order->extra_info / 100;
	num_of_records->test = num_of_records->total - num_of_records->train;
	if (dataset_split_order->dataset_split_mode == E_BEGIN)
		dataset_type_array = split_with_mode_begin(num_of_records);
	else if (dataset_split_order->dataset_split_mode == E_END)
		dataset_type_array = split_with_mode_end(num_of_records);
	else if (dataset_split_order->dataset_split_mode == E_RAND)
		dataset_type_array = split_with_mode_end(num_of_records);
	else
		dataset_type_array = split_with_mode_begin(num_of_records);
	return (dataset_type_array);
}
