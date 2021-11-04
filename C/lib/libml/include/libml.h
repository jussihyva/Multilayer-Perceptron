/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libml.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:32:39 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/04 18:36:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBML_H
# define LIBML_H
# include "libft_addons.h"

typedef enum e_sign
{
	E_MINUS,
	E_PLUS
}				t_sign;

typedef struct s_matrix
{
	t_matrix_size	size;
	void			**values;
}				t_matrix;

const t_matrix		*ft_sigmoid(const t_matrix *const input);
t_matrix			*ft_matrix_create(size_t size, const size_t rows,
						const size_t columns);
void				ft_double_div_matrix(const double value,
						const t_matrix *const matrix,
						t_matrix *const new_matrix);
void				ft_matrix_exp(const t_matrix *const matrix,
						t_matrix *const new_matrix, const t_sign sign);
void				ft_matrix_add_double(const t_matrix *const matrix,
						const double value, t_matrix *const new_matrix);
void				ft_matrix_remove(t_matrix **matrix);
void				ft_matrix_print(const char *const matrix_name,
						const t_matrix *const matrix);

#endif
