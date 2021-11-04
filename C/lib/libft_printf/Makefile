# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/04 11:34:07 by jkauppi           #+#    #+#              #
#    Updated: 2021/11/04 15:00:53 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS			=	$(shell uname -s)
CUR_DIR		=	$(abspath .)

ifeq ($(OS), Darwin)
	SHELL				=	zsh
endif

NAME1				=	libftprintf.a
C_ARCHIVES			=	$(NAME1)

LIBFT_FOLDER	=	../libft

# Folders
OBJ				=	obj
SRC				=	src
INCLUDE			=	include
FOLDERS			=	$(OBJ) $(SRC) $(INCLUDE)
INCLUDES		=	-I $(INCLUDE) -I $(LIBFT_FOLDER)

# Compiler and linking parameters
OS				=	$(shell uname -s)
CC				=	clang
C_FLAGS			=	-std=gnu17 -fPIE -g -Wall -Wextra -Werror $(INCLUDES)

# C (Source code) and H (Header) files
SRC_C_FILES		=	ft_printf.c split_input_string.c create_converters.c \
					ft_lltoa_base.c ft_ulltoa_base.c param_type.c \
					width_and_prediction.c modify_character.c \
					modify_string.c modify_pointer.c modify_integer.c \
					modify_octal.c modify_hex.c modify_unsigned_integer.c \
					release_memory_2.c read_param.c modify_float.c \
					formatters.c ft_dtoa_base.c ft_numlen.c ft_round.c \
					set_substring_common_1.c set_substring_common_2.c \
					set_substring_zero.c \
					print_output_string.c ft_putlstr_fd.c release_memory_1.c
SRC_H_FILES		=	ft_printf.h

# Path folders for H, C, O and APP files
H_FILES			=	$(addprefix $(INCLUDE)/, $(SRC_H_FILES))
C_FILES			=	$(addprefix $(SRC)/, $(SRC_C_FILES))
O_FILES			=	$(addprefix $(OBJ)/, $(patsubst %.c, %.o, $(SRC_C_FILES)))

# Target files (Object archive and H files)
TARGET_C_ARCHIVES	=	$(addprefix ../, $(C_ARCHIVES))
TARGET_H_FILES		=	$(addprefix ../, $(notdir $(H_FILES)))

# Colours for printouts
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
END				=	\033[0m

.PHONY: all
all: libraries $(TARGET_C_ARCHIVES) $(TARGET_H_FILES)
	@echo -n ""

$(TARGET_H_FILES): $(H_FILES) Makefile
	@for file in $(H_FILES) ; do \
	    cp $$file ../ ; \
		echo "File $(YELLOW)$$file$(END) -> $(GREEN)../`basename $$file`$(END) copied!" ; \
	done

$(TARGET_C_ARCHIVES): Makefile $(C_ARCHIVES) | prepare
	@cp $(notdir $@) $@
	@echo "File $(YELLOW)$(notdir $@)$(END) -> $(GREEN)$@$(END) copied!"

$(C_ARCHIVES): $(O_FILES)
	@ar -rcs $@ $(O_FILES)

$(O_FILES): $(OBJ)/%.o: $(SRC)/%.c $(H_FILES) Makefile
	@$(CC) -c -o $@ $< $(C_FLAGS)
	@echo "    File $(YELLOW)$<$(END) -> $(GREEN)$@$(END) compiled!"

.PHONY: prepare
prepare: $(FOLDERS) $(C_FILES)

$(FOLDERS):
	mkdir $@

$(C_FILES):
	touch $@

.PHONY: libraries
libraries:
	@make -C ${LIBFT_FOLDER}

.PHONY: clean
clean:
	@make -C ${LIBFT_FOLDER} clean
	rm -f $(O_FILES)

.PHONY: fclean
fclean: clean
	@make -C ${LIBFT_FOLDER} fclean
	rm -f $(C_ARCHIVES)
	rm -f $(TARGET_C_ARCHIVES)
	rm -f $(TARGET_H_FILES)

.PHONY: re
re: fclean all

.PHONY: norm
norm:
ifeq ($(OS), Darwin)
	norminette
else
	norminette
endif
