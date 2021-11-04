/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:29:59 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/04 18:37:02 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

void	ft_matrix_print(
					const char *const matrix_name,
					const t_matrix *const matrix)
{
	t_matrix_size	i;
	size_t			cnt;
	const double	**values;

	values = (const double **)matrix->values;
	cnt = -1;
	ft_printf("%s\n", matrix_name);
	i.rows = -1;
	while (++i.rows < matrix->size.rows)
	{
		cnt++;
		ft_printf("%lu: ", cnt);
		i.columns = -1;
		while (++i.columns < matrix->size.columns)
			ft_printf("%10f ", ((double **)matrix->values)[i.rows][i.columns]);
		ft_printf("\n");
	}
	return ;
}
