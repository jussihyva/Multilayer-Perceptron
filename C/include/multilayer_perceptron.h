/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilayer_perceptron.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:25:55 by jkauppi           #+#    #+#             */
/*   Updated: 2022/07/03 14:31:06 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTILAYER_PERCEPTRON_H
# define MULTILAYER_PERCEPTRON_H
# include "libml.h"
# include <libgen.h>

# define NUM_OF_DATASETS						2
# define NUM_OF_LAYERS							4
# define NUMBER_OF_COLUMNS						32
# define NUMBER_OF_OUTPUT_FUNCTIONS				2
# define NUM_INFLUXDB_ELEMENTS					4
# define SPECIAL_CHARS_INFLUXDB_MEASUREMENT		", "
# define SPECIAL_CHARS_INFLUXDB_TAGS			", ="
# define SPECIAL_CHARS_INFLUXDB_FIELDS			", ="
# define LEARNING_RATE							1.0
# define NUM_OF_EPOCH							5000
# define BIAS_WEIGHT_FILE						"/../Data/BiasWeight.yml"
# define SUB_STRING_MAX_LENGTH					100
# define ONE_NODE								1
# define TWO_NODES								2
# define THREE_NODES							3
# define FOUR_NODES								4
# define FIVE_NODES								5
# define MAX_RESULT_OF_LINEAR_CALCULATION		1.0e+4

typedef enum e_activation_type
{
	E_NO_ACTIVATION,
	E_SIGMOID,
	E_RELU
}			t_activation_type;

typedef enum e_layer_type
{
	E_LAYER_INPUT,
	E_LAYER_HIDDEN,
	E_LAYER_OUTPUT
}				t_layer_type;

typedef enum e_data_type
{
	E_SIZE_T,
	E_DOUBLE,
	E_STRING
}				t_data_type;

typedef struct s_key_value_pair
{
	void			*key;
	t_data_type		key_type;
	void			*value;
	t_data_type		value_type;
}				t_key_value_pair;

typedef struct s_layer_profile
{
	size_t				nodes;
	t_layer_type		layer_type;
	t_activation_type	activation_type;
}				t_layer_profile;

static const t_layer_profile	g_two_layers[2]
	= {{NUMBER_OF_COLUMNS - 2, E_LAYER_INPUT, E_NO_ACTIVATION},
{NUMBER_OF_OUTPUT_FUNCTIONS, E_LAYER_OUTPUT, E_SIGMOID}};

static const t_layer_profile	g_three_layers[3]
	= {{NUMBER_OF_COLUMNS - 2, E_LAYER_INPUT, E_NO_ACTIVATION},
{THREE_NODES, E_LAYER_HIDDEN, E_RELU},
{NUMBER_OF_OUTPUT_FUNCTIONS, E_LAYER_OUTPUT, E_SIGMOID}};

static const t_layer_profile	g_four_layers[4]
	= {{NUMBER_OF_COLUMNS - 2, E_LAYER_INPUT, E_NO_ACTIVATION},
{THREE_NODES, E_LAYER_HIDDEN, E_SIGMOID},
{THREE_NODES, E_LAYER_HIDDEN, E_SIGMOID},
{NUMBER_OF_OUTPUT_FUNCTIONS, E_LAYER_OUTPUT, E_SIGMOID}};

static const t_layer_profile	g_five_layers[5]
	= {{NUMBER_OF_COLUMNS - 2, E_LAYER_INPUT, E_NO_ACTIVATION},
{THREE_NODES, E_LAYER_HIDDEN, E_RELU},
{FIVE_NODES, E_LAYER_HIDDEN, E_RELU},
{THREE_NODES, E_LAYER_HIDDEN, E_RELU},
{NUMBER_OF_OUTPUT_FUNCTIONS, E_LAYER_OUTPUT, E_SIGMOID}};

static const t_layer_profile	*g_layer_attrs[6]
	= {NULL, NULL, g_two_layers, g_three_layers, g_four_layers, g_five_layers};

static const char				*g_dataset_file_column_names[NUMBER_OF_COLUMNS]
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

static const t_bool				g_dataset_file_y_columns[NUMBER_OF_COLUMNS]
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

typedef enum e_split_mode
{
	E_BEGIN,
	E_END,
	E_RAND
}			t_split_mode;

typedef struct s_split_order
{
	t_split_mode	split_mode;
	size_t			extra_info;
}			t_split_order;

typedef struct s_input_data
{
	size_t						num_of_input_functions;
	const char *const *const	*input_record_array;
	const t_dataset_type		*dataset_type_array;
	t_num_of_records			num_of_records;
	t_dataset					**dataset_array;
	t_input_function_attr		*input_function_attrs;
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

typedef enum s_weight_init_mode
{
	E_ZERO,
	E_RAND_0_TO_1,
	E_TRAINED
}				t_weight_init_mode;

typedef struct s_weight_bias
{
	t_matrix		*weight;
	t_vector		*bias;
}				t_weight_bias;

typedef struct s_hyper_params
{
	size_t					num_of_layers;
	size_t					*num_of_nodes;
	size_t					epochs;
	double					learning_rate;
	t_bool					is_early_stop;
	t_split_order			split_order;
	t_weight_init_mode		weight_init_mode;
	t_weight_bias			*bias_weight_init_values;
	t_activation_type		*activation_types;
}				t_hyper_params;

typedef struct s_layer_input
{
	size_t					id;
	t_layer_type			layer_type;
	size_t					num_of_nodes;
	const t_matrix			*x;
	const t_matrix			*x_train;
	const t_matrix			*x_test;
	t_fn_normalize			fn_normalize;
	t_matrix				*a;
	t_matrix				*a_train;
	t_matrix				*a_test;
	const t_hyper_params	*hyper_params;
	t_dataset_type			dataset_type;
}				t_layer_input;

typedef struct s_layer_hidden
{
	size_t					id;
	t_layer_type			layer_type;
	size_t					num_of_nodes;
	t_weight_bias			weight_bias;
	t_matrix				*z;
	t_matrix				*z_train;
	t_matrix				*z_test;
	t_matrix				*a;
	t_matrix				*a_train;
	t_matrix				*a_test;
	t_weight_bias			d_weight_bias;
	t_matrix				*d_z;
	const t_hyper_params	*hyper_params;
	const t_matrix			*g_prime;
	const t_matrix			*weight_transposed;
	t_dataset_type			dataset_type;
	t_activation_type		activation_type;
}				t_layer_hidden;

typedef struct s_layer_output
{
	size_t					id;
	t_layer_type			layer_type;
	size_t					num_of_nodes;
	t_weight_bias			weight_bias;
	t_matrix				*z;
	t_matrix				*z_train;
	t_matrix				*z_test;
	t_matrix				*y_hat;
	t_matrix				*y_hat_train;
	t_matrix				*y_hat_test;
	const t_matrix			*y;
	t_matrix				*y_train;
	t_matrix				*y_test;
	t_vector				*cost[NUM_OF_DATASETS];
	t_weight_bias			d_weight_bias;
	t_matrix				*d_z;
	const t_hyper_params	*hyper_params;
	t_dataset_type			dataset_type;
	t_activation_type		activation_type;
	const t_matrix			*softmax;
	const t_vector			*argmax;
	const t_vector			*argmax_values;
}				t_layer_output;

typedef struct s_neural_network
{
	void					**layers;
	const t_layer_type		*layer_types;
}				t_neural_network;

typedef struct s_grad_descent_attr
{
	const t_dataset				*dataset;
	const t_neural_network		*neural_network;
	const t_hyper_params		*hyper_params;
	const char					*weight_bias_file;
	const t_tcp_connection		*influxdb_connection;
}				t_grad_descent_attr;

typedef struct s_influxdb_elem
{
	char		*measurement;
	char		*tag_set;
	char		*field_set;
	const char	*timestamp;
}				t_influxdb_elem;

typedef struct s_cmd_args
{
	const t_argc_argv		*argc_argv;
	const t_logging_data	*logging_data;
	t_logging_level			logging_level;
	t_bool					print_leaks;
	t_bool					is_influxdb;
	const char				*dataset_file;
	char					*dataset_test_file;
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

t_dataset				**dataset_init(const t_input_data *const input_data);
void					file_attr_remove(t_file_attr **file_attr);
void					dataset_remove(t_dataset **dataset);
void					derivative_z_cost(const t_matrix *const y_hat,
							const t_matrix *const y,
							t_matrix *const derivative_z);
void					derivative_w(const t_matrix *const x,
							const t_matrix *const derivative_z,
							t_matrix *const derivative_w);
void					derivative_b(const t_matrix *const derivative_z,
							t_vector *const derivative_b);
void					linear_function_hidden(
							const t_layer_hidden *const layer,
							const t_matrix *const activation_input);
void					linear_function_output(
							const t_layer_output *const layer,
							const t_matrix *const activation_input);
t_neural_network		*neural_network_init(
							t_dataset **dataset_array,
							const t_hyper_params *const hyper_params);
void					grad_descent_attr_remove(
							t_grad_descent_attr **grad_descent_attr);
t_grad_descent_attr		*grad_descent_attr_initialize(
							const t_input_data *const input_data,
							const char *const weight_bias_file,
							const t_hyper_params *const hyper_params);
size_t					grad_descent(
							const t_neural_network *const neural_network,
							const t_hyper_params *const hyper_params,
							const t_tcp_connection *const influxdb_connection);
void					send_iteration_result_to_database(
							const t_tcp_connection *const influxdb_connection,
							const t_layer_output *const layer_output,
							const size_t iter_cnt);
void					*arg_init_train(t_argc_argv *argc_argv);
void					*arg_init_predict(t_argc_argv *argc_argv);
void					arg_analyze(void *const cmd_args, char opt,
							void *arg_parser, t_cmd_param_type cmd_param_type);
void					arg_usage_training(void);
void					arg_usage_prediction(void);
void					arg_remove(const t_cmd_args **cmd_args);
void					normalize(const t_matrix *const input,
							const t_matrix *const output);
void					bias_weight_values_save(void *const *const layers,
							const t_layer_type *const layer_types,
							t_read_attr *const read_attr,
							const t_hyper_params *const hyper_params);
void					neural_network_save(void *const *const layers,
							const t_layer_type *const layer_types,
							const char *const weight_bias_file,
							const t_hyper_params *const hyper_params);
void					bias_weight_values_set(
							void *const *const layers,
							const t_layer_type *const layer_types,
							const t_hyper_params *const hyper_params);
void					send_softmax_result_to_database(
							const t_tcp_connection *const influxdb_connection,
							t_queue *const key_value_queue,
							const t_matrix *const softmax,
							const size_t example_id);
t_prediction			*prediction_init(const int argc,
							const char *const *const argv);
t_training				*training_init(const int argc,
							const char *const *const argv);
size_t					set_num_of_epochs(const t_argc_argv *const argc_argv);
size_t					set_num_of_layers(const t_argc_argv *const argc_argv);
double					set_learning_rate(const t_argc_argv *const argc_argv);
t_bool					*prediction_validate(const t_matrix *const observed,
							const t_vector *const argmax);
void					update_content_of_matrix(
							const t_file_attr *const file_attr,
							const size_t *const valid_columns,
							t_dataset *const dataset);
void					g_prime(
							const t_matrix *const z,
							const t_matrix *const a,
							const t_matrix *const g_prime,
							const t_activation_type activation_type);
const t_matrix			*get_activation_input(
							void *const layer,
							const t_layer_type layer_type);
void					propagation_forward(void *const *const layers,
							const t_layer_type *const layer_types,
							const size_t num_of_layers);
void					propagation_backward(void *const *const layers,
							const t_layer_type *const layer_types,
							const size_t num_of_layers);
void					bias_update(const size_t layer_id,
							const t_vector *const bias,
							const t_vector *const d_bias,
							const t_hyper_params *const hyper_params);
void					weight_update(const size_t layer_id,
							const t_matrix *const weight,
							const t_matrix *const d_weight,
							const t_hyper_params *const hyper_params);
void					send_layer_stat_to_database(
							const t_tcp_connection	*influxdb_connection,
							void *const *const layers,
							const t_layer_type *const layer_types,
							const size_t num_of_layers);
void					send_weight_values_to_database(
							const size_t layer_id,
							const t_matrix *const weight,
							const t_hyper_params *const hyper_params);
const t_tcp_connection	*get_database_connection(void);
void					influxdb_elem_remove(t_influxdb_elem *influxdb_elem);
void					influxdb_line_extend(
							const t_influxdb_elem *const influxdb_elem,
							size_t len,
							char **const line);
size_t					influxdb_elem_string_create(char **const elem_string,
							t_queue *key_value_queue);
size_t					influxdb_timestamp(const char **const timestamp);
void					neural_network_remove(
							const t_neural_network **const neural_network,
							const size_t num_of_layers);
void					*layer_init(
							const size_t i,
							const t_layer_type layer_type,
							t_dataset **dataset_array,
							const t_hyper_params *const hyper_params);
void					bias_weight_init(
							const t_size_2d size,
							t_weight_bias *const weight_bias,
							t_name *const row_name_array,
							const t_weight_init_mode weight_init_mode);
void					layer_print_input(const t_layer_input *const layer);
void					layer_print_hidden_f(const t_layer_hidden *const layer);
void					layer_print_hidden_b(const t_layer_hidden *const layer);
void					layer_print_output_f(const t_layer_output *const layer);
void					layer_print_output_b(const t_layer_output *const layer);
void					layer_remove_input(t_layer_input **layer);
void					layer_remove_hidden(t_layer_hidden **layer);
void					layer_remove_output(t_layer_output **layer);
t_input_data			*input_data_init(const char *const dataset_file,
							const t_split_order *split_order);
void					input_data_remove(t_input_data **input_data);
const t_split_order		*set_split_mode(const t_argc_argv *const argc_argv,
							t_split_order *const split_order);
t_dataset_type			*dataset_split(t_num_of_records *const num_of_records,
							const t_split_order *split_order);
void					layer_mode_set(
							const t_neural_network *const neural_network,
							const t_dataset_type dataset_type,
							const size_t num_of_layers);
t_weight_init_mode		set_weight_init_mode(
							const t_argc_argv *const argc_argv);
void					send_hyper_params_to_database(
							const t_tcp_connection *const influxdb_connection,
							const t_hyper_params *const hyper_params);
size_t					influxdb_timestamp_set(const char **const timestamp);
t_hyper_params			*hyper_params_init(
							const char *const weight_bias_file,
							const t_hyper_params *const input_hyper_params,
							const size_t num_of_input_functions);
t_layer_type			set_layer_type(const size_t id,
							const size_t num_of_layers);
void					hyper_params_remove(t_hyper_params **hyper_params);
void					get_hyper_params_from_file(
							const char *const weight_bias_file,
							const size_t num_of_input_functions,
							t_hyper_params	*hyper_params);
void					bias_weight_values_read(
							t_weight_bias *const bias_weight,
							const char *const *const *const row_array,
							size_t *const row_id);
t_bool					string_convert_and_validate(
							const char *string,
							const t_data_type data_type,
							void *value);
void					derivative_z(
							const t_matrix *const d_z,
							const t_layer_hidden *const layer);
const char				*get_layer_stat_hidden(
							const t_layer_hidden *const layer,
							const size_t layer_id);
const char				*get_layer_stat_output(
							const t_layer_output *const layer,
							const size_t layer_id);
void					bias_stat_add(
							char **const line,
							const t_vector *const bias,
							const t_hyper_params *const hyper_params,
							const size_t layer_id);
void					weight_stat_add(
							char **const line,
							const t_matrix *const weight,
							const t_hyper_params *const hyper_params,
							const size_t layer_id);
size_t					influxdb_key_value_pair_string_create(
							const t_key_value_pair *const key_value_pair,
							const char *const special_chars,
							char **const string);
char					*influxdb_special_chars_conv(
							const char *const special_chars,
							const char *const string);
size_t					get_measurement_value(
							const char *const measurement,
							t_queue *const queue);
size_t					add_record_type(
							const char *const record_type,
							const char *const special_chars,
							t_queue *const key_value_queue);
void					prediction_result(
							t_grad_descent_attr *grad_descent_attr);
t_layer_output			*layer_init_output(
							const size_t id,
							t_dataset **dataset_array,
							const size_t *num_of_examples,
							const t_hyper_params *const hyper_params);
void					arg_param_save_short(
							t_cmd_args *const cmd_args,
							char opt,
							t_arg_parser *arg_parser);
char					*set_dataset_test_file(
							const t_argc_argv *const argc_argv);
void					send_accuracy_result_to_database(
							const t_tcp_connection *const influxdb_connection,
							t_queue *const key_value_queue,
							const t_bool *const accuracy_array,
							const size_t example_id);
void					cost_values_print(
							const size_t iter_cnt,
							const size_t epochs,
							const t_layer_output *const layer_output);

#endif
