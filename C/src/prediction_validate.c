/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prediction_validate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhani <juhani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:40:40 by juhani            #+#    #+#             */
/*   Updated: 2021/11/23 13:42:39 by juhani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	prediction_validate(
					const t_matrix *const observed,
					const t_vector *const argmax)
{
	size_t		i;
	size_t		predicted_value;
	size_t		num_of_right_predictions;

	num_of_right_predictions = 0;
	i = -1;
	while (++i < observed->size.cols)
	{
		predicted_value = ((double *)argmax->data)[i];
		if (((double **)observed->table)[predicted_value][i])
			num_of_right_predictions++;
	}
	ft_printf("Accuracy score: %.2f\n", num_of_right_predictions
		/ (double)observed->size.cols);
	return ;
}
