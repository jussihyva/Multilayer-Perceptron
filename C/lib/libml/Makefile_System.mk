# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_System.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/31 15:56:00 by juhani            #+#    #+#              #
#    Updated: 2021/11/04 15:11:55 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS					=	$(shell uname -s)
CUR_DIR				=	$(abspath .)

ifeq ($(OS), Darwin)
	SHELL			=	zsh
endif

SYSTEM_INCLUDE		=
ifeq ($(OS), Darwin)
	D_ATTRIBUTES	=	-D DARWIN
endif

# Colours for printouts
RED					=	\033[0;31m
GREEN				=	\033[0;32m
YELLOW				=	\033[0;33m
GRAY				=	\033[1;30m
PURPLE				=	\033[0;35m
END					=	\033[0m
