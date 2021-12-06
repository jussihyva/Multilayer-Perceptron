# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_Source_Files.mk                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 11:06:20 by jkauppi           #+#    #+#              #
#    Updated: 2021/12/06 12:04:04 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_C_FILES				=	dataset_read.c file_attr_remove.c \
							dataset_remove.c derivative.c \
							logistic_regression.c neural_network_init.c \
							linear_function.c grad_descent.c \
							send_iteration_result_to_database.c arg_init.c \
							arg_analyze.c arg_usage_print.c arg_remove.c \
							normalize.c bias_weight_values_save.c \
							bias_weight_values_set.c \
							send_softmax_result_to_database.c \
							prediction_init.c training_init.c \
							hyper_params.c prediction_validate.c \
							dataset_init.c layer.c propagation_backward.c \
							g_prime.c propagation_forward.c
SRC_H_FILES				=	multilayer_perceptron.h
LOCAL_LIBS				=	libml.a libft_addons.a libftprintf.a libft.a
GLOBAL_LIBS				=	libssl.a libcrypto.a
GLOBAL_LIB_FOLDERS		=

ifeq ($(OS), Darwin)
	GLOBAL_LIBS			+=
	GLOBAL_LIB_FOLDERS	+=	$(HOME)/.brew/Cellar/openssl@3/3.0.0_1/lib
else
	GLOBAL_LIBS			+=	libm.a
endif
