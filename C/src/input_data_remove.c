/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_data_remove.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 20:01:48 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/14 20:22:43 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	input_data_remove(t_input_data **input_data)
{
	size_t		i;

	i = -1;
	while (++i < NUM_OF_DATASETS)
		dataset_remove(&(*input_data)->dataset_array[i]);
	ft_memdel((void **)&(*input_data)->dataset_array);
	ft_memdel((void **)&(*input_data)->valid_input_column_ids);
	ft_memdel((void **)&(*input_data)->dataset_type_array);
	ft_memdel((void **)input_data);
	return ;
}
