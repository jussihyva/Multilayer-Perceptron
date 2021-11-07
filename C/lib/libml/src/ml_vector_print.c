/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_vector_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:33:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/07 13:40:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ml_vector_print(
				const char *const name,
				const t_vector *const vector)
{
	const double	*data;
	size_t			cnt;
	size_t			i;

	data = (const double *)vector->data;
	cnt = -1;
	ft_printf("%s\n", name);
	i = -1;
	while (++i < vector->size)
	{
		cnt++;
		ft_printf("%lu: ", cnt);
		ft_printf("%10f ", data[i]);
		ft_printf("\n");
	}
	return ;
}
