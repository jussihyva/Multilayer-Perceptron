/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilayer_perceptron.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:25:55 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/07 13:07:53 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTILAYER_PERCEPTRON_H
# define MULTILAYER_PERCEPTRON_H
# include "libml.h"
# include <libgen.h>

# define NUM_OF_LAYERS							4
# define INPUT_LAYER_ID							0
# define OUTPUT_LAYER_ID						NUM_OF_LAYERS - 1
# define NUMBER_OF_COLUMNS						32
# define NUM_INFLUXDB_ELEMENTS					4
# define SPECIAL_CHARS_INFLUXDB_MEASUREMENT		", "
# define SPECIAL_CHARS_INFLUXDB_TAGS			", ="
# define SPECIAL_CHARS_INFLUXDB_FIELDS			", ="
# define LEARNING_RATE							1.0
# define NUM_OF_EPOCH							5000
# define BIAS_WEIGHT_FILE						"/../Data/BiasWeight.yml"
# define SUB_STRING_MAX_LENGTH					100

typedef enum e_layer_type
{
	E_LAYER_INPUT,
	E_LAYER_HIDDEN,
	E_LAYER_OUTPUT
}				t_layer_type;

typedef struct s_layer_profile
{
	size_t			nodes;
	t_layer_type	layer_type;
}				t_layer_profile;

static const t_layer_profile	g_layer_attrs[NUM_OF_LAYERS]
	= {{NUMBER_OF_COLUMNS, E_LAYER_INPUT}, {3, E_LAYER_HIDDEN}, {3, E_LAYER_HIDDEN}, {2, E_LAYER_OUTPUT}};
	// = {{NUMBER_OF_COLUMNS, E_LAYER_INPUT}, {2, E_LAYER_OUTPUT}};

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

typedef void					(*t_fn_normalize)(const t_matrix *const,
									const t_matrix *const);
typedef void					(*t_fn_linear)(const t_matrix *const,
									const t_matrix *const,
									const t_vector *const,
									const t_matrix *const);
typedef void					(*t_fn_non_linear)(const t_matrix *const,
									const t_matrix *const);

typedef struct s_database
{
	const t_tcp_connection	*connection;
}				t_database;

typedef struct s_hyper_params
{
	size_t		epochs;
	double		learning_rate;
}				t_hyper_params;

typedef struct s_weight_bias
{
	t_matrix		*weight;
	t_vector		*bias;
}				t_weight_bias;

typedef struct s_layer_input
{
	size_t					id;
	t_layer_type			layer_type;
	size_t					num_of_nodes;
	const t_matrix			*x;
	t_fn_normalize			fn_normalize;
	t_matrix				*a;
	const t_hyper_params	*hyper_params;
}				t_layer_input;

typedef struct s_layer_hidden
{
	size_t					id;
	t_layer_type			layer_type;
	size_t					num_of_nodes;
	t_weight_bias			weight_bias;
	t_matrix				*z;
	t_matrix				*a;
	t_weight_bias			d_weight_bias;
	t_matrix				*d_z;
	const t_hyper_params	*hyper_params;
	const t_matrix			*g_prime;
	const t_matrix			*weight_transposed;
}				t_layer_hidden;

typedef struct s_layer_output
{
	size_t					id;
	t_layer_type			layer_type;
	size_t					num_of_nodes;
	t_weight_bias			weight_bias;
	t_matrix				*z;
	t_matrix				*y_hat;
	const t_matrix			*y;
	t_vector				*cost;
	t_weight_bias			d_weight_bias;
	t_matrix				*d_z;
	const t_hyper_params	*hyper_params;
}				t_layer_output;

typedef struct s_neural_network
{
	const void					**layers;
	t_layer_type				*layer_types;
}				t_neural_network;

typedef struct s_grad_descent_attr
{
	const t_dataset				*dataset;
	const t_neural_network		*neural_network;
	const t_hyper_params		*hyper_params;
	const char					*weight_bias_file;
	const t_matrix				*softmax;
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
void				dataset_remove(const t_dataset **dataset);
void				derivative_z_cost(const t_matrix *const y_hat,
						const t_matrix *const y, t_matrix *const derivative_z);
void				derivative_w(const t_matrix *const x,
						const t_matrix *const derivative_z,
						t_matrix *const derivative_w);
void				derivative_b(const t_matrix *const derivative_z,
						t_vector *const derivative_b);
// void				logistic_regression(const t_layer *const layer);
void				linear_function_hidden(const t_layer_hidden *const layer,
						const t_matrix *const activation_input);
void				linear_function_output(const t_layer_output *const layer,
						const t_matrix *const activation_input);
t_neural_network	*neural_network_init(const t_dataset *const dataset,
						const t_hyper_params *const hyper_params);
void				grad_descent_attr_remove(
						t_grad_descent_attr **grad_descent_attr);
t_grad_descent_attr	*grad_descent_attr_initialize(
						const char *const dataset_file,
						const char *const weight_bias_file,
						const t_hyper_params *const hyper_params);
void				grad_descent(
						const t_neural_network *const neural_network,
						const t_hyper_params *const hyper_params,
						const t_tcp_connection *const influxdb_connection);
void				send_iteration_result_to_database(
						const t_tcp_connection *const influxdb_connection,
						const void *const *const layers,
						const size_t iter_cnt);
void				*arg_init(t_argc_argv *argc_argv);
void				arg_analyze(void *const cmd_args, char opt,
						void *arg_parser, t_cmd_param_type cmd_param_type);
void				arg_usage_training(void);
void				arg_usage_prediction(void);
void				arg_remove(const t_cmd_args **cmd_args);
void				normalize(const t_matrix *const input,
						const t_matrix *const output);
void				bias_weight_values_save(
						const t_vector *const bias,
						const t_matrix *const weight,
						const char *const weight_bias_file);
void				bias_weight_values_set(
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
void				propagation_forward_input(
						const t_layer_input *const layer);
void				propagation_forward_hidden(
						const t_layer_hidden *const layer,
						const t_matrix *const activation_input);
void				propagation_forward_output(
						const t_layer_output *const layer,
						const t_matrix *const activation_input);
void				g_prime_sigmoid(const t_matrix *const a,
						const t_matrix *const g_prime);
const t_matrix		*get_activation_input(
						const t_neural_network *const neural_network,
						const size_t layer_id);
void				propagation_forward(const t_neural_network
						*const neural_network);
void				propagation_backward(const t_neural_network
						*const neural_network);
void				bias_update(const size_t layer_id,
						const t_vector *const bias,
						const t_vector *const d_bias,
						const double learning_rate);
void				weight_update(const size_t layer_id,
						const t_matrix *const weight,
						const t_matrix *const d_weight,
						const double learning_rate);
void				send_bias_values_to_database(
						const size_t layer_id,
						const t_vector *const bias,
						const t_hyper_params *const hyper_params);
const t_tcp_connection	*get_database_connection(void);

#endif
