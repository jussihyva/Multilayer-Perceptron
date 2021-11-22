/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libml.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:32:39 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/22 14:54:16 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBML_H
# define LIBML_H
# include "libft_addons.h"
# include <time.h>
# include <float.h>

# define EPSILON		0.0000001

typedef enum e_sign
{
	E_MINUS,
	E_PLUS
}				t_sign;

typedef struct s_size_2d
{
	size_t	rows;
	size_t	cols;
}				t_size_2d;

typedef struct s_name_array
{
	const char		**names;
	size_t			*lengths;
}				t_name_array;

typedef struct s_matrix
{
	t_size_2d			size;
	void				*data;
	void				**table;
	t_name_array		row_names;
	t_name_array		column_names;
}				t_matrix;

typedef struct s_vector
{
	size_t				size;
	void				*data;
	const t_name_array	column_names;
}				t_vector;

void			ml_sigmoid(const t_matrix *const z, t_matrix *const y);
t_matrix		*ml_matrix_create(const size_t rows, const size_t columns);
void			ml_double_div_matrix(const double value,
					const t_matrix *const matrix,
					t_matrix *const new_matrix);
void			ml_matrix_exp(const t_matrix *const matrix,
					t_matrix *const new_matrix, const t_sign sign);
void			ml_matrix_add_double(const t_matrix *const matrix,
					const double value, t_matrix *const new_matrix);
void			ml_matrix_remove(t_matrix **matrix);
void			ml_vector_remove(t_vector **vector);
void			ml_matrix_print(const char *const name,
					const t_matrix *const matrix);
void			ml_matrix_rand(t_matrix *const matrix, const int min,
					const int max);
void			ml_matrix_cost(const t_matrix *const y,
					const t_matrix *const y_hat, t_vector *const cost_vector);
t_vector		*ml_vector_create(const size_t length);
void			ml_vector_print(const char *const name,
					const t_vector *const vector);
int				ml_fast_rand(void);
void			ml_vector_rand(t_vector *const vector, const int min,
					const int max);
void			ml_vector_reset(t_vector *const vector);
void			ml_matrix_reset(t_matrix *const matrix);
const t_vector	*ml_matrix_min(const t_matrix *const matrix);
const t_vector	*ml_matrix_max(const t_matrix *const matrix);
void			ml_vector_set(const t_vector *const vector, const double value);
void			ml_softmax(const t_matrix *const matrix,
					const t_matrix *const softmax);
void			ml_argmax(const t_matrix *const matrix,
					const t_vector *const argmax,
					const t_vector *argmax_values);
void			ml_transpose(const t_matrix *const matrix,
					const t_matrix *const transposed);

#endif
