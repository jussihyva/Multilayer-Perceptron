/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilayer_perceptron.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:25:55 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/13 19:50:59 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTILAYER_PERCEPTRON_H
# define MULTILAYER_PERCEPTRON_H
# include "libml.h"

# define NEURAL_NETWORK_NUM_OF_LAYERS			1
# define NUMBER_OF_COLUMNS						32

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
static const t_bool	g_dataset_file_x_columns[NUMBER_OF_COLUMNS]
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
static const t_bool	g_dataset_file_y_columns[NUMBER_OF_COLUMNS]
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

typedef struct s_layer
{
	size_t		num_of_nodes;
	t_matrix	*a;
	t_matrix	*weight;
	t_vector	*bias;
	t_matrix	*z;
	t_matrix	*y_hat;
	t_vector	*derivative_z;
	t_matrix	*derivative_w;
	t_vector	*derivative_b;
}				t_layer;

typedef struct s_neural_network
{
	t_layer		*layers;
}				t_neural_network;

typedef struct s_logistic_reg_attributes
{
	t_neural_network	*neural_network;
	t_vector			*cost;
	t_vector			*derivative_y_hat;
}				t_logistic_reg_attributes;

typedef struct s_grad_descent_attributes
{
	t_dataset			*dataset;
}				t_grad_descent_attributes;

t_dataset			*read_dataset(const char *const file_path);
void				file_attributes_remove(t_file_attributes **file_attributes);
void				dataset_remove(t_dataset **dataset);
t_vector			*calculate_derivative_z(t_matrix *y_hat, t_matrix *y);
t_matrix			*calculate_derivative_w(t_matrix *x,
						t_vector *derivative_z);
t_vector			*calculate_derivative_b(t_vector *derivative_z);
void				logistic_regression(
						const t_grad_descent_attributes \
						*const grad_descent_attributes,
						t_logistic_reg_attributes \
						*const logistic_reg_attributes);
void				linear_function(const t_layer *const layer);
t_neural_network	*neural_network_initialize(t_dataset *dataset);
void				logistic_reg_attributes_remove(
						t_logistic_reg_attributes **logistic_reg_attributes);

#endif
