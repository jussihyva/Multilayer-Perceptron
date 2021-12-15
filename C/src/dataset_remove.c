/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 23:23:40 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/15 12:55:10 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	dataset_remove(t_dataset **dataset)
{
	size_t		i;

	i = -1;
	// while (++i < (*dataset)->x->size.rows)
	// {
	// 	ft_strdel((*dataset)->x->row_name_array[i].name);
	// }
	// ft_strarraydel(&(*dataset)->x->column_names.names,
	// 	(*dataset)->x->size.cols);
	// ft_strarraydel(&(*dataset)->x->row_names.names,
	// 	(*dataset)->x->size.rows);
	// ft_memdel((void **)&(*dataset)->x->column_names.lengths);
	// ft_memdel((void **)&(*dataset)->x->row_names.lengths);
	// ml_matrix_remove((t_matrix **)&(*dataset)->x);
	// ft_strarraydel(&(*dataset)->y->column_names.names,
	// 	(*dataset)->y->size.cols);
	// ft_strarraydel(&(*dataset)->y->row_names.names,
	// 	(*dataset)->y->size.rows);
	// ft_memdel((void **)&(*dataset)->y->column_names.lengths);
	// ft_memdel((void **)&(*dataset)->y->row_names.lengths);
	// ml_matrix_remove((t_matrix **)&(*dataset)->y);
	ft_memdel((void **)dataset);
	return ;
}
