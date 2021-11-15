# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/20 10:35:04 by ubuntu            #+#    #+#              #
#    Updated: 2021/11/15 16:51:30 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include Makefile_System.mk

C_PROGRAMS				=	training prediction
C_FOLDER				=	C
SUB_FOLDERS				=	Python Data Documentation .vscode
SUB_FOLDERS_WITH_MAKE	=	Docker $(C_FOLDER) Jupyter
VS_CODE_FILE			=	workspace.code-workspace

define VS_CODE_CONTENT
{\n\
\t"folders": [\n\
\t\t{\n\
\t\t\t"path": "."\n\
\t\t}\n\
\t]\n\
}\n
endef

define OPENSSL_ERROR

	OPENSSL is not installed:

		1. For Hive MAC's:	brew install openssl

		
endef

.PHONY: all
all: required_apps help

include Makefile_Help.mk

$(C_PROGRAMS): build

.PHONY: build
build: required_apps check_openssl check_docker $(SUB_FOLDERS) $(SUB_FOLDERS_WITH_MAKE) folders $(VS_CODE_FILE) start_jupyter
	@echo -n "$(GREEN)"
	@echo "DONE"
	@echo -n "$(END)"

.PHONY: run
run:
	make -C C run

$(SUB_FOLDERS):
	@mkdir $@

$(SUB_FOLDERS_WITH_MAKE):
	@mkdir $@
	@echo "all:\n\t@echo -n \"\"" > $@/Makefile

.PHONY: folders
folders:
	@echo -n "$(PURPLE)"
	@echo "Compile sub folders:"
	@for folder in $(SUB_FOLDERS_WITH_MAKE) ; do \
		echo -n "$(PURPLE)" ; \
		echo "  $$folder" ; \
		echo -n "$(END)" ; \
		make --no-print-directory -C $$folder SHELL=$(SHELL); \
	done
	@echo "$(END)"

$(VS_CODE_FILE):
	echo '$(VS_CODE_CONTENT)' > $(VS_CODE_FILE)

.PHONY: clean
clean:
	for folder in $(SUB_FOLDERS_WITH_MAKE) ; do \
		make -C $$folder clean ; \
	done

.PHONY: fclean
fclean:
	for folder in $(SUB_FOLDERS_WITH_MAKE) ; do \
		make -C $$folder fclean ; \
	done

.PHONY: re
re: all
	for folder in $(SUB_FOLDERS_WITH_MAKE) ; do \
		make -C $$folder re ; \
	done

.PHONY: norm
norm:
	for folder in $(C_FOLDER) ; do \
		make -C $$folder norm ; \
	done

.PHONY: check_openssl
check_openssl:

.PHONY: start_jupyter
start_jupyter:
	cd Jupyter ; jupyter notebook

include Makefile_Required.mk