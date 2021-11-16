/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilayer_perceptron.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:25:55 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/16 14:17:08 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTILAYER_PERCEPTRON_H
# define MULTILAYER_PERCEPTRON_H
# include "libml.h"

# define NEURAL_NETWORK_NUM_OF_LAYERS			1
# define NUMBER_OF_COLUMNS						32
# define NUM_INFLUXDB_ELEMENTS					4
# define SPECIAL_CHARS_INFLUXDB_MEASUREMENT		", "
# define SPECIAL_CHARS_INFLUXDB_TAGS			", ="
# define SPECIAL_CHARS_INFLUXDB_FIELDS			", ="

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
	t_vector	*derivative_y_hat;
	t_matrix	*derivative_z;
	t_matrix	*derivative_w;
	t_vector	*derivative_b;
}				t_layer;

typedef struct s_hyper_params
{
	double		learning_rate;
	size_t		iters;
}				t_hyper_params;

typedef struct s_neural_network
{
	t_layer		*layers;
}				t_neural_network;

typedef struct s_logistic_reg_attr
{
	t_neural_network	*neural_network;
}				t_logistic_reg_attr;

typedef struct s_grad_descent_attr
{
	t_dataset				*dataset;
	t_logistic_reg_attr		*logistic_reg_attr;
	t_hyper_params			*hyper_params;
	t_vector				*cost;
	t_tcp_connection		*connection;
}				t_grad_descent_attr;

typedef enum e_influxdb_elem_type
{
	E_MEASUREMENT,
	E_TAGS,
	E_FIELDS,
	E_TIMESTAMP
}				t_influxdb_elem_type;

typedef struct s_influxdb_elem
{
	const char	*string;
	size_t		length;
}				t_influxdb_elem;

t_dataset			*read_dataset(const char *const file_path);
void				file_attr_remove(t_file_attr **file_attr);
void				dataset_remove(t_dataset **dataset);
void				calculate_derivative_z(const t_matrix *const y_hat,
						const t_matrix *const y, t_matrix *const derivative_z);
void				calculate_derivative_w(const t_matrix *const x,
						const t_matrix *const derivative_z,
						t_matrix *const derivative_w);
void				calculate_derivative_b(const t_matrix *const derivative_z,
						t_vector *const derivative_b);
void				logistic_regression(t_layer *const layer);
void				linear_function(const t_layer *const layer);
t_neural_network	*neural_network_initialize(t_dataset *dataset);
void				grad_descent_attr_remove(
						t_grad_descent_attr **grad_descent_attr);
void				logistic_reg_attr_remove(
						t_logistic_reg_attr **logistic_reg_attr);
t_grad_descent_attr	*grad_descent_attr_initialize(void);
void				grad_descent(t_grad_descent_attr *grad_descent_attr);
void				send_iteration_result_to_database(
						const t_grad_descent_attr *const grad_descent_attr);

#endif
