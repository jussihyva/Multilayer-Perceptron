# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_System.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/31 15:56:00 by juhani            #+#    #+#              #
#    Updated: 2021/10/31 18:02:19 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS			=	$(shell uname -s)
CUR_DIR		=	$(abspath .)

ifeq ($(OS), Darwin)
	SHELL				=	zsh
endif

PIP3					=	$(shell which pip3)
DOCKER_NAME				=	$(shell which docker)
DOCKER-COMPOSE_NAME		=	$(shell which docker-compose)
JUPYTER_NAME			=	$(shell which jupyter | egrep jupyter)
PYTHON_NUMPY_VER		=	$(shell pip3 list | egrep "^numpy ")
PYTHON_MATPLOTLIB_VER	=	$(shell pip3 list | egrep "^matplotlib ")
PYTHON_PANDAS_VER		=	$(shell pip3 list | egrep "^pandas ")

SYSTEM_INCLUDE		=
ifeq ($(OS), Darwin)
	SYSTEM_INCLUDE	+=	-I $(HOME)/.brew/Cellar/openssl@1.1/1.1.1k/include
	SYSTEM_INCLUDE	+=	-I $(HOME)/.brew/Cellar/openssl@1.1/1.1.1l/include
endif

define PIP3_NOT_INSTALLED_ERROR

	pip3 is not installed:

		- For Linux
			1. sudo apt-get install python3-pip

endef
