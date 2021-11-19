/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:29:59 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/19 13:35:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

static void	print_columns(const t_name_array *const names, const size_t len)
{
	size_t		i;

	if (names->names)
	{
		ft_printf("      ");
		i = -1;
		while (++i < len)
			ft_printf("%*s", names->lengths[i] + 2, names->names[i]);
		ft_printf("\n");
	}
	return ;
}

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
	print_columns(&matrix->column_names, matrix->size.cols);
	i.rows = -1;
	while (++i.rows < matrix->size.rows)
	{
		cnt++;
		ft_printf("%4lu: ", cnt);
		i.cols = -1;
		while (++i.cols < matrix->size.cols)
		{
			if (matrix->column_names.lengths)
				ft_printf("%*f", matrix->column_names.lengths[i.cols] + 2,
					((double **)matrix->table)[i.rows][i.cols]);
			else
				ft_printf("%10f", ((double **)matrix->table)[i.rows][i.cols]);
		}
		ft_printf("\n");
	}
	return ;
}
