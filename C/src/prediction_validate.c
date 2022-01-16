/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prediction_validate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:40:40 by juhani            #+#    #+#             */
/*   Updated: 2022/01/16 23:56:03 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

t_bool	*prediction_validate(
					const t_matrix *const observed,
					const t_vector *const argmax)
{
	size_t		i;
	size_t		predicted_value;
	size_t		num_of_right_predictions;
	t_bool		*accuracy_array;

	accuracy_array = ft_memalloc(sizeof(*accuracy_array) * argmax->size);
	num_of_right_predictions = 0;
	i = -1;
	while (++i < observed->size.cols)
	{
		predicted_value = ((double *)argmax->data)[i];
		if (((double **)observed->table)[predicted_value][i])
		{
			num_of_right_predictions++;
			accuracy_array[i] = E_TRUE;
		}
		else
			FT_LOG_INFO("Observation of the example ID %lu is not right");
	}
	ft_printf("Accuracy score: %.2f\n", num_of_right_predictions
		/ (double)observed->size.cols);
	return (accuracy_array);
}
