# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_Help.mk                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 12:26:25 by jkauppi           #+#    #+#              #
#    Updated: 2021/11/24 11:23:24 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: help
help:
	@echo "$(GRAY)"
	@echo "Docker                   : ${DOCKER_NAME}"
	@echo "Docker compose           : ${DOCKER-COMPOSE_NAME}"
	@echo "Jupyter                  : ${JUPYTER_NAME}"
	@echo "Python numpy ver         : ${PYTHON_NUMPY_VER}"
	@echo "Python matplotlib ver    : ${PYTHON_MATPLOTLIB_VER}"
	@echo "Python pandas ver        : ${PYTHON_PANDAS_VER}"
	@echo "$(END)"
	@echo ""
	@echo "$(GREEN)"
	@echo "1. Installation"
	@echo "  make build"
	@echo ""
	@echo "2. Run the program"
	@echo "  make run"
	@echo ""
	@echo "3. Help"
	@for program in $(C_PROGRAMS) ; do \
		echo "  $(CUR_DIR)/$$program -h" ; \
	done
	@echo ""
	@echo "4. Readme"
	@echo "  README.rd file includes implemantation realted information"
	@echo "$(YELLOW)"
ifneq (Darwin, $(OS))
	@echo "Required ubuntu programs:"
	@for module in `cat requirements_ubuntu.txt` ; do \
		echo "  $$module" ; \
	done
endif
	@echo "Required python3 modules:"
	@for module in `cat requirements_python.txt` ; do \
		echo "  $$module" ; \
	done
	@echo "$(END)"
	@echo ""
