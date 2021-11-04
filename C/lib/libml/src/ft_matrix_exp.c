/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:25:52 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/04 18:59:15 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

static double	do_exp(double value, const int sign_value)
{
	double	new_value;

	value *= sign_value;
	new_value = exp(value);
	return (new_value);
}

void	ft_matrix_exp(
				const t_matrix *const matrix,
				t_matrix *const new_matrix,
				const t_sign sign)
{
	t_vector_size		i;
	const double		**values;
	double				**new_values;
	int					sign_value;

	if (sign == E_PLUS)
		sign_value = 1;
	else
		sign_value = -1;
	values = (const double **)matrix->values;
	new_values = (double **)new_matrix->values;
	i.rows = -1;
	while (++i.rows < matrix->size.rows)
	{
		i.columns = -1;
		while (++i.columns < matrix->size.columns)
			new_values[i.rows][i.columns]
				= do_exp(values[i.rows][i.columns], sign_value);
	}
	return ;
}
