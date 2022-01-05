/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 23:23:40 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/05 23:07:12 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	dataset_remove(t_dataset **dataset)
{
	size_t		i;
	size_t		dataset_id;

	dataset_id = -1;
	i = -1;
	while (++i < (*dataset)->x->size.rows)
	{
		// ft_strdel((char **)&(*dataset)->x->row_name_array[i].name);
		// ft_strarraydel(&(*dataset)->x->row_names.names,
		// 	(*dataset)->x->size.rows);
	}
	while (++i < (*dataset)->x->size.cols)
	{
		// ft_strdel((char **)&(*dataset)->x->col_name_array[i].name);
	}
	ft_memdel((void **)&(*dataset)->x->col_name_array);
	ft_memdel((void **)&(*dataset)->x->row_name_array);
	ml_matrix_remove((t_matrix **)&(*dataset)->x);
	// ft_strarraydel(&(*dataset)->y->column_names.names,
	// 	(*dataset)->y->size.cols);
	// ft_strarraydel(&(*dataset)->y->row_names.names,
	// 	(*dataset)->y->size.rows);
	ft_memdel((void **)&(*dataset)->y->col_name_array);
	ft_memdel((void **)&(*dataset)->y->row_name_array);
	ml_matrix_remove((t_matrix **)&(*dataset)->y);
	ft_memdel((void **)dataset);
	return ;
}
