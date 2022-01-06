/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 23:23:40 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/06 21:13:33 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	dataset_remove(t_dataset **dataset)
{
	size_t		i;
	size_t		dataset_id;

	dataset_id = -1;
	i = -1;
	ft_memdel((void **)&(*dataset)->x->col_name_array);
	ft_memdel((void **)&(*dataset)->x->row_name_array);
	ml_matrix_remove((t_matrix **)&(*dataset)->x);
	ft_memdel((void **)&(*dataset)->y->col_name_array);
	ft_memdel((void **)&(*dataset)->y->row_name_array);
	ml_matrix_remove((t_matrix **)&(*dataset)->y);
	ft_memdel((void **)dataset);
	return ;
}
