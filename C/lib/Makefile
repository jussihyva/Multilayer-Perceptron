# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 17:02:16 by jkauppi           #+#    #+#              #
#    Updated: 2021/11/04 15:00:14 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS			=	$(shell uname -s)
CUR_DIR		=	$(abspath .)

ifeq ($(OS), Darwin)
	SHELL				=	zsh
endif

# Colours for printouts
RED						=	\033[0;31m
GREEN					=	\033[0;32m
YELLOW					=	\033[0;33m
GRAY					=	\033[1;30m
PURPLE					=	\033[0;35m
END						=	\033[0m

LIB_FOLDERS		=	libft libft_printf libft_addons

.PHONY: all
all: libraries

.PHONY: libraries
libraries:
	@for folder in $(LIB_FOLDERS) ; do \
		echo -n "$(PURPLE)" ; \
		echo "  $$folder" ; \
		echo -n "$(END)" ; \
	    make --no-print-directory -C $$folder ; \
	done

.PHONY: clean
clean:
	for folder in $(LIB_FOLDERS) ; do \
	    make -C $$folder clean ; \
	done

.PHONY: fclean
fclean:
	for folder in $(LIB_FOLDERS) ; do \
		make -C $$folder fclean ; \
	done

.PHONY: re
re: all
	for folder in $(LIB_FOLDERS) ; do \
	    make -C $$folder re ; \
	done

.PHONY: norm
norm:
	for folder in $(LIB_FOLDERS) ; do \
	    make -C $$folder norm ; \
	done
