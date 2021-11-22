# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_Source_Files.mk                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/07 14:28:42 by jkauppi           #+#    #+#              #
#    Updated: 2021/11/22 14:30:59 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_C_FILES		=	ml_matrix_create.c ml_matrix_exp.c \
					ml_matrix_add_double.c ml_matrix_remove.c \
					ml_double_div_matrix.c ml_matrix_print.c \
					ml_sigmoid.c ml_matrix_rand.c \
					ml_matrix_cost.c ml_vector_create.c \
					ml_vector_print.c ml_vector_rand.c \
					ml_vector_remove.c ml_fast_rand.c \
					ml_matrix_reset.c ml_vector_reset.c \
					ml_matrix_min.c ml_matrix_max.c \
					ml_vector_set.c ml_softmax.c ml_argmax.c ml_transpose.c
SRC_H_FILES		=	libml.h
