# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_Required.mk                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/31 16:27:38 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/31 18:03:01 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: required_apps
required_apps: check_pip3 check_docker check_jupyter

.PHONY: check_pip3
check_pip3:
ifeq (, $(PIP3))
	$(error $(PIP3_NOT_INSTALLED_ERROR))
endif

.PHONY: check_docker
check_docker:
ifeq (, $(DOCKER_NAME))
	$(error $(DOCKER_NOT_INSTALLED_ERROR))
else ifeq (, $(DOCKER-COMPOSE_NAME))
	$(error $(DOCKER_COMPOSE_NOT_INSTALLED_ERROR))
endif

.PHONY: check_jupyter
check_jupyter:
ifeq (, $(JUPYTER_NAME))
	$(error $(JUPYTER_NOT_INSTALLED_ERROR))
	# pip3 install notebook
endif
ifeq (, $(PYTHON_NUMPY_VER))
	pip3 install numpy
endif
ifeq (, $(PYTHON_MATPLOTLIB_VER))
	pip3 install matplotlib
endif
ifeq (, $(PYTHON_PANDAS_VER))
	pip3 install pandas
endif

define DOCKER_NOT_INSTALLED_ERROR

	Docker is not installed:

		- For MAC (At Hive)
			1. Download alexandregv/42toolbox (github) and run init_docker.sh
			2. ./init_docker.sh

		- For Linux
			1. sudo apt-get install docker.io
		
endef

define DOCKER_COMPOSE_NOT_INSTALLED_ERROR

	Docker-compose is not installed:

		- For MAC (At Hive)
			1. Download alexandregv/42toolbox (github) and run init_docker.sh
			2. ./init_docker.sh

		- For Linux
			1. sudo apt-get install docker-compose
		
endef

define JUPYTER_NOT_INSTALLED_ERROR

	Docker is not installed:

		- For Linux
			1. sudo apt-get install jupyter

endef
