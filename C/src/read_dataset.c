/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dataset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:00:14 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/11 20:13:48 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "training.h"

t_matrix	*read_dataset(const char *const file_path)
{
	t_file_attributes	*file_attributes;
	t_matrix			*dataset;

	file_attributes = ft_read_file(file_path, E_CSV);
	ft_strarray_print(file_attributes->row_array[0]);
	dataset = ml_matrix_create(4, 5);
	file_attributes_remove(&file_attributes);
	return (dataset);
}