/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilayer_perceptron.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhani <juhani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:25:55 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/30 23:18:07 by juhani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTILAYER_PERCEPTRON_H
# define MULTILAYER_PERCEPTRON_H
# include "libml.h"
# include <libgen.h>

# define NUM_OF_LAYERS							4
# define NUMBER_OF_COLUMNS						32
# define NUM_INFLUXDB_ELEMENTS					4
# define SPECIAL_CHARS_INFLUXDB_MEASUREMENT		", "
# define SPECIAL_CHARS_INFLUXDB_TAGS			", ="
# define SPECIAL_CHARS_INFLUXDB_FIELDS			", ="
# define LEARNING_RATE							0.2
# define NUM_OF_EPOCH							5000
# define BIAS_WEIGTH_FILE						"/../Data/BiasWeigth.yml"
# define SUB_STRING_MAX_LENGTH					100

static const t_bool				g_dataset_file_x_columns[NUMBER_OF_COLUMNS]
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
	// E_FALSE,
	// E_FALSE,
	// E_FALSE,
	// E_FALSE,
	// E_FALSE,
	// E_FALSE,
	// E_FALSE,
	// E_FALSE,
	// E_FALSE,
	// E_FALSE,
	// E_FALSE,
	// E_FALSE,
	// E_FALSE,
	// E_FALSE,
	// E_FALSE,
	// E_FALSE,
	// E_FALSE,
	// E_FALSE,
	// E_FALSE,
	// E_FALSE};
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

typedef enum e_layer_type
{
	E_LAYER_INPUT,
	E_LAYER_HIDDEN,
	E_LAYER_OUTPUT
}				t_layer_type;

typedef void					(*t_fn_normalize)(const t_matrix *const,
									const t_matrix *const);
typedef void					(*t_fn_linear)(const t_matrix *const,
									const t_matrix *const,
									const t_vector *const,
									const t_matrix *const);
typedef void					(*t_fn_non_linear)(const t_matrix *const,
									const t_matrix *const);
typedef void					(*t_fn_layer_forward_propagation)(const void *const);
typedef void					(*t_fn_layer_backward_propagation)(const void *const);

typedef struct s_layer_input
{
	size_t				id;
	size_t				num_of_nodes;
	const t_matrix		*x_input;
	t_fn_normalize		fn_normalize;
	t_matrix			*x_output;
}				t_layer_input;

typedef struct s_layer_hidden
{
	size_t			num_of_nodes;
	const t_matrix	*a_input;
	t_matrix		*weight;
	t_vector		*bias;
	t_matrix		*z;
	t_matrix		*a_output;
	t_matrix		*d_weight;
	t_vector		*d_bias;
	t_matrix		*d_z;
}				t_layer_hidden;

typedef struct s_layer_output
{
	size_t					num_of_nodes;
	const t_matrix *const	y_hat;
	const t_matrix *const	y;
	t_vector				*cost;
}				t_layer_output;

typedef struct s_hyper_params
{
	size_t		epochs;
	double		learning_rate;
}				t_hyper_params;

typedef struct s_neural_network
{
	const void						**layers;
	t_fn_layer_forward_propagation	*fn_layer_forward_propagation;
	t_fn_layer_backward_propagation	*fn_layer_backward_propagation;
}				t_neural_network;

typedef struct s_layer_profile
{
	size_t		nodes;
}				t_layer_profile;

typedef struct s_logistic_reg_attr
{
	t_neural_network	*neural_network;
}				t_logistic_reg_attr;

typedef struct s_grad_descent_attr
{
	t_dataset					*dataset;
	t_logistic_reg_attr			*logistic_reg_attr;
	const t_hyper_params		*hyper_params;
	const char					*weight_bias_file;
	const t_vector				*cost;
	t_matrix					*softmax;
	const t_vector				*argmax;
	const t_vector				*argmax_values;
	const t_tcp_connection		*influxdb_connection;
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

typedef struct s_cmd_args
{
	const t_argc_argv		*argc_argv;
	const t_logging_data	*logging_data;
	t_logging_level			logging_level;
	t_bool					print_leaks;
	t_bool					is_influxdb;
	const char				*dataset_file;
	const char				*weight_bias_file;
	t_hyper_params			hyper_params;
}				t_cmd_args;

typedef struct s_training
{
	t_argc_argv				argc_argv;
	t_arg_parser			*arg_parser;
	const t_cmd_args		*cmd_args;
	t_grad_descent_attr		*grad_descent_attr;
}				t_training;

typedef struct s_prediction
{
	t_argc_argv				argc_argv;
	t_arg_parser			*arg_parser;
	const t_cmd_args		*cmd_args;
	t_grad_descent_attr		*grad_descent_attr;
}				t_prediction;

t_dataset			*dataset_init(const char *const file_path);
void				file_attr_remove(t_file_attr **file_attr);
void				dataset_remove(t_dataset **dataset);
void				calculate_derivative_z(const t_matrix *const y_hat,
						const t_matrix *const y, t_matrix *const derivative_z);
void				calculate_derivative_w(const t_matrix *const x,
						const t_matrix *const derivative_z,
						t_matrix *const derivative_w);
void				calculate_derivative_b(const t_matrix *const derivative_z,
						t_vector *const derivative_b);
// void				logistic_regression(const t_layer *const layer);
// void				linear_function(const t_layer *const layer);
t_neural_network	*neural_network_init(const t_dataset *const dataset);
void				grad_descent_attr_remove(
						t_grad_descent_attr **grad_descent_attr);
void				logistic_reg_attr_remove(
						t_logistic_reg_attr **logistic_reg_attr);
t_grad_descent_attr	*grad_descent_attr_initialize(
						const char *const dataset_file,
						const char *const weight_bias_file,
						const t_hyper_params *const hyper_params);
const t_vector		*grad_descent(
						const t_neural_network *const neural_network,
						const t_dataset *const dataset,
						const t_hyper_params *const hyper_params,
						const t_tcp_connection *const influxdb_connection);
void				send_iteration_result_to_database(
						const t_tcp_connection *const influxdb_connection,
						const t_vector *const cost,
						const size_t iter_cnt);
void				*arg_init(t_argc_argv *argc_argv);
void				arg_analyze(void *const cmd_args, char opt,
						void *arg_parser, t_cmd_param_type cmd_param_type);
void				arg_usage_training(void);
void				arg_usage_prediction(void);
void				arg_remove(const t_cmd_args **cmd_args);
void				normalize(const t_matrix *const input,
						const t_matrix *const output);
void				bias_weigth_values_save(
						const t_vector *const bias,
						const t_matrix *const weight,
						const char *const weight_bias_file);
void				bias_weigth_values_set(
						const t_vector *const bias,
						const t_matrix *const weight,
						const char *const weight_bias_file);
void				send_softmax_result_to_database(
						const t_grad_descent_attr *const grad_descent_attr);
t_prediction		*prediction_init(const int argc,
						const char *const *const argv);
t_training			*training_init(const int argc,
						const char *const *const argv);
size_t				set_number_of_epochs(const t_argc_argv *const argc_argv);
double				set_learning_rate(const t_argc_argv *const argc_argv);
void				prediction_validate(const t_matrix *const observed,
						const t_vector *const argmax);
void				update_content_of_matrix_y(const char ***row_array,
						const size_t rows, t_matrix **matrix);
t_matrix			*update_content_of_matrix(const char ***row_array,
						size_t *valid_columns, t_matrix *matrix);
size_t				*get_valid_columns_and_create_matrix(
						const size_t rows,
						const t_bool *const array_of_valid_columns,
						t_matrix **matrix);
t_logistic_reg_attr	*logistic_reg_init(const t_dataset *const dataset);
void				layer_input_calculation(const void *const layer);

#endif
