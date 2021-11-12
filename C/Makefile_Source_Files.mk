# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_Source_Files.mk                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 11:06:20 by jkauppi           #+#    #+#              #
#    Updated: 2021/11/12 18:39:50 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_C_FILES				=	read_dataset.c file_attributes_remove.c \
							dataset_remove.c derivative.c
SRC_H_FILES				=
LOCAL_LIBS				=	libml.a libft_addons.a libftprintf.a libft.a 
GLOBAL_LIBS				=
GLOBAL_LIB_FOLDERS		=

ifeq ($(OS), Darwin)
	GLOBAL_LIBS			+=
	GLOBAL_LIB_FOLDERS	+=
else
	GLOBAL_LIBS			+=	libm.a
endif
