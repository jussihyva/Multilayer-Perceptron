/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:29:59 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/07 13:44:30 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ml_matrix_print(
					const char *const name,
					const t_matrix *const matrix)
{
	t_size_2d		i;
	size_t			cnt;
	const double	**values;

	values = (const double **)matrix->table;
	cnt = -1;
	ft_printf("%s\n", name);
	i.rows = -1;
	while (++i.rows < matrix->size.rows)
	{
		cnt++;
		ft_printf("%lu: ", cnt);
		i.cols = -1;
		while (++i.cols < matrix->size.cols)
			ft_printf("%10f ", ((double **)matrix->table)[i.rows][i.cols]);
		ft_printf("\n");
	}
	return ;
}
