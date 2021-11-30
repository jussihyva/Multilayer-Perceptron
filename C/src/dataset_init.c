/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhani <juhani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:13:48 by juhani            #+#    #+#             */
/*   Updated: 2021/11/30 23:06:28 by juhani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

t_dataset	*dataset_init(const char *const file_path)
{
	t_file_attr		*file_attr;
	t_dataset		*dataset;
	size_t			*valid_columns;

	dataset = NULL;
	file_attr = ft_read_file(file_path, E_CSV);
	if (!file_attr || file_attr->read_failure)
		FT_LOG_ERROR("Reading of file %s failed!", file_path);
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
		// normalize(dataset->x);
	}
	file_attr_remove(&file_attr);
	return (dataset);
}
