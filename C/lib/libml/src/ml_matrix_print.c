/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:29:59 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/15 13:30:17 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libml.h"

static void	print_columns(
				const t_name *const column_name_array,
				const size_t len)
{
	size_t		i;

	if (column_name_array && column_name_array[0].name)
	{
		ft_printf("      ");
		i = -1;
		while (++i < len)
			ft_printf("%*s", column_name_array[i].len + 2,
				column_name_array[i].name);
		ft_printf("\n");
	}
	return ;
}

static void	print_value(
					const double value,
					const size_t length,
					const size_t i,
					const size_t total)
{
	if (total < 30 || (i < 15 || i > (total - 15)))
	{
		if (length)
			ft_printf("%*f", length + 2, value);
		else
			ft_printf("%10f", value);
	}
	else if (i == ((size_t)(total / 2)))
		ft_printf(" ...  ");
	return ;
}

void	ml_matrix_print(
					const char *const name,
					const t_matrix *const matrix)
{
	t_size_2d		i;
	size_t			cnt;
	const double	**values;
	double			value;

	values = (const double **)matrix->table;
	cnt = -1;
	ft_printf("%s\n", name);
	print_columns(matrix->col_name_array, matrix->size.cols);
	i.rows = -1;
	while (++i.rows < matrix->size.rows)
	{
		cnt++;
		ft_printf("%4lu: ", cnt);
		i.cols = -1;
		while (++i.cols < matrix->size.cols)
		{
			value = ((double **)matrix->table)[i.rows][i.cols];
			print_value(value, matrix->col_name_array[i.cols].len, i.cols,
				matrix->size.cols);
		}
		ft_printf("\n");
	}
	return ;
}
