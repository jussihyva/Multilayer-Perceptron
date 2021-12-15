/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilayer_perceptron.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:25:55 by jkauppi           #+#    #+#             */
/*   Updated: 2021/12/15 14:21:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTILAYER_PERCEPTRON_H
# define MULTILAYER_PERCEPTRON_H
# include "libml.h"
# include <libgen.h>

# define NUM_OF_DATASETS						2
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

static const t_layer_profile	g_two_layers[3]
	= {{NUMBER_OF_COLUMNS - 2, E_LAYER_INPUT}, {2, E_LAYER_OUTPUT}};
static const t_layer_profile	g_three_layers[3]
	= {{NUMBER_OF_COLUMNS - 2, E_LAYER_INPUT}, {3, E_LAYER_HIDDEN}, {2, E_LAYER_OUTPUT}};
static const t_layer_profile	g_four_layers[4]
	= {{NUMBER_OF_COLUMNS - 2, E_LAYER_INPUT}, {3, E_LAYER_HIDDEN}, {3, E_LAYER_HIDDEN}, {2, E_LAYER_OUTPUT}};
static const t_layer_profile	*g_layer_attrs[5] = {NULL, NULL, g_two_layers, g_three_layers, g_four_layers};

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

typedef struct s_num_of_records
{
	size_t		total;
	size_t		train;
	size_t		test;
}			t_num_of_records;

typedef struct s_input_function_attr
{
	size_t			column_id;
	const char		*name;
	size_t			name_len;
}			t_input_function_attr;

typedef struct s_input_data
{
	size_t					num_of_input_functions;
	size_t					num_of_output_functions;
	const char				*const *const *input_record_array;
	const t_dataset_type	*dataset_type_array;
	t_num_of_records		num_of_records;
	t_dataset				**dataset_array;
	t_input_function_attr	*input_function_attrs;
}			t_input_data;

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
	const void				**layers;
	const t_layer_type		*layer_types;
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

typedef struct s_influxdb_line
{
	const char	*measurement;
	const char	*tag_set;
	const char	*field_set;
	const char	*timestamp;
}				t_influxdb_line;

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
	t_input_data			*input_data;
}				t_training;

typedef struct s_prediction
{
	t_argc_argv				argc_argv;
	t_arg_parser			*arg_parser;
	const t_cmd_args		*cmd_args;
	t_grad_descent_attr		*grad_descent_attr;
	t_input_data			*input_data;
}				t_prediction;

typedef enum e_influxdb_field_type
{
	E_SIZE_T,
	E_DOUBLE,
	E_STRING
}				t_influxdb_field_type;

t_dataset			**dataset_init(const t_input_data *const input_data);
void				file_attr_remove(t_file_attr **file_attr);
void				dataset_remove(t_dataset **dataset);
void				derivative_z_cost(const t_matrix *const y_hat,
						const t_matrix *const y, t_matrix *const derivative_z);
void				derivative_w(const t_matrix *const x,
						const t_matrix *const derivative_z,
						t_matrix *const derivative_w);
void				derivative_b(const t_matrix *const derivative_z,
						t_vector *const derivative_b);
void				linear_function_hidden(const t_layer_hidden *const layer,
						const t_matrix *const activation_input);
void				linear_function_output(const t_layer_output *const layer,
						const t_matrix *const activation_input);
t_neural_network	*neural_network_init(const t_dataset *const dataset,
						const t_hyper_params *const hyper_params);
void				grad_descent_attr_remove(
						t_grad_descent_attr **grad_descent_attr);
t_grad_descent_attr	*grad_descent_attr_initialize(
						const t_input_data *const input_data,
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
void				bias_weight_values_save(const void *const *const layers,
						const t_layer_type *const layer_types,
						const char *const weight_bias_file);
void				bias_weight_values_set(
						const void *const *const layers,
						const t_layer_type *const layer_types,
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
						const size_t rows, t_dataset *const dataset);
void				update_content_of_matrix(const t_file_attr *const file_attr,
						const size_t *const valid_columns, t_dataset *const dataset);
size_t				*get_valid_columns_and_create_matrix(
						const size_t rows,
						const t_bool *const array_of_valid_columns,
						t_dataset *const dataset);
void				g_prime_sigmoid(const t_matrix *const a,
						const t_matrix *const g_prime);
const t_matrix		*get_activation_input(
						const void *const *const layers,
						const t_layer_type *const layer_types,
						const size_t layer_id);
void				propagation_forward(const void *const *const layers,
						const t_layer_type *const layer_types,
						const size_t epochs,
						const size_t iter_cnt);
void				propagation_backward(const void *const *const layers,
						const t_layer_type *const layer_types,
						const size_t epochs, const size_t iter_cnt);
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
void				send_weight_values_to_database(
						const size_t layer_id,
						const t_matrix *const weight,
						const t_hyper_params *const hyper_params);
const t_tcp_connection	*get_database_connection(void);
size_t				influxdb_measurement(const char **const measurement,
						const char *const string);
void				influxdb_line_remove(t_influxdb_line *influxdb_line);
void				influxdb_line_merge(
						const t_influxdb_line *const influxdb_line,
						size_t total_len,
						const char **const line);
size_t				influxdb_tag_set(
						const char **const tag_set,
						t_queue *const name_value_queue);
size_t				influxdb_field_set(const char **const field_set,
						const double *const data, const size_t size);
size_t				influxdb_timestamp(const char **const timestamp);
void				neural_network_remove(
						const t_neural_network **const neural_network);
const void			*layer_init(
						const size_t i,
						const t_layer_type layer_type,
						const t_dataset *const dataset,
						const t_hyper_params *const hyper_params);
void				bias_weight_init(
						const size_t id,
						t_weight_bias *const weight_bias,
						t_name *const row_name_array);
void				layer_print_input(const t_layer_input *const layer);
void				layer_print_output(const t_layer_output *const layer);
void				layer_remove_input(const t_layer_input **const layer);
void				layer_remove_hidden(const t_layer_hidden **const layer);
void				layer_remove_output(const t_layer_output **const layer);
t_input_data		*input_data_init(const char *const dataset_file);
void				input_data_remove(t_input_data **input_data);

#endif
