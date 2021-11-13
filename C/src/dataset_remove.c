/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 23:23:40 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/13 14:27:53 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	dataset_remove(t_dataset **dataset)
{
	ml_matrix_remove(&(*dataset)->x);
	ml_matrix_remove(&(*dataset)->y);
	ft_memdel((void **)dataset);
	return ;
}
