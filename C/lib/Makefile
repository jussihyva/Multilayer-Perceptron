# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 17:02:16 by jkauppi           #+#    #+#              #
#    Updated: 2021/11/03 23:01:12 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

A_FILES				=	libft/libft.a libft_printf/libftprintf.a \
						libft_addons/libft_addons.a
H_FILES				=	libft/libft.h libft_printf/include/ft_printf.h \
						libft_addons/include/libft_addons.h \
						libft_addons/include/libft_addons_against_norm.h
LIB_FOLDERS			=	$(dir $(A_FILES))

.PHONY: all
all: h_files $(A_FILES) libraries

.PHONY: h_files
h_files: $(H_FILES)
	@cp -f $^ ./

.PHONY: libraries
libraries:
	@for folder in $(LIB_FOLDERS) ; do \
	    make --no-print-directory -C $$folder ; \
	done

.PHONY: clean
clean:
	for folder in $(LIB_FOLDERS) ; do \
	    make -C $$folder clean ; \
	done
	rm -f $(notdir $(H_FILES))
	rm -f $(notdir $(A_FILES))

.PHONY: fclean
fclean:
	for folder in $(LIB_FOLDERS) ; do \
		make -C $$folder fclean ; \
	done
	rm -f $(notdir $(H_FILES))
	rm -f $(notdir $(A_FILES))

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
