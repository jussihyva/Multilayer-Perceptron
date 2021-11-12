/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:25:55 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/12 20:21:51 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRAINING_H
# define TRAINING_H
# include "libml.h"

# define NUMBER_OF_COLUMNS		32

static const char	*g_dataset_file_column_names[NUMBER_OF_COLUMNS]
		= {"ID number", "Diagnosis", "Mean Radius", "Mean Texture",
			"Mean Perimeter", "Mean Area", "Mean Smoothness",
			"Mean Compactness", "Mean Concavity", "Mean Concave points",
			"Mean Symmetry", "Mean Fractal dimension", "Radius SE",
			"Texture SE", "Perimeter SE", "Area SE", "Smoothness SE",
			"Compactness SE", "Concavity SE", "Concave points SE",
			"Symmetry SE", "Fractal dimension SE", "Worst Radius",
			"Worst Texture", "Worst Perimeter", "Worst Area",
			"Worst Smoothness", "Worst Compactness", "Worst Concavity",
			"Worst Concave points", "Worst Symmetry",
			"Worst Fractal dimension"};
static const t_bool		g_dataset_file_x_columns[NUMBER_OF_COLUMNS]
													= {E_FALSE,
														E_FALSE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE,
														E_TRUE};
static const t_bool		g_dataset_file_y_columns[NUMBER_OF_COLUMNS]
													= {E_FALSE,
														E_TRUE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE,
														E_FALSE};

typedef enum e_dataset_type
{
	E_TRAIN,
	E_TEST
}			t_dataset_type;

typedef struct s_dataset
{
	t_matrix	*x;
	t_matrix	*y;
}			t_dataset;

t_dataset	*read_dataset(const char *const file_path);
void		file_attributes_remove(t_file_attributes **file_attributes);
void		dataset_remove(t_dataset **dataset);
t_vector	*calculate_derivative_of_z(t_matrix *y_hat, t_matrix *y);
t_matrix	*calculate_derivative_of_w(t_matrix *x, t_vector *derivative_z);

#endif
