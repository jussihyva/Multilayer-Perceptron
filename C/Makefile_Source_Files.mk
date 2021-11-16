# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_Source_Files.mk                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 11:06:20 by jkauppi           #+#    #+#              #
#    Updated: 2021/11/16 11:35:29 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_C_FILES				=	read_dataset.c file_attr_remove.c \
							dataset_remove.c derivative.c \
							logistic_regression.c neural_network_initialize.c \
							linear_function.c grad_descent.c \
							send_iteration_result_to_database.c
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
