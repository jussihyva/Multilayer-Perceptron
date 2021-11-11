# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/04 11:34:07 by jkauppi           #+#    #+#              #
#    Updated: 2021/11/11 19:31:05 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS			=	$(shell uname -s)
CUR_DIR		=	$(abspath .)

ifeq ($(OS), Darwin)
	SHELL				=	zsh
endif

NAME1				=	libftprintf.a
C_ARCHIVES			=	$(NAME1)

# Folders
OBJ				=	obj
SRC				=	src
INCLUDE			=	include
FOLDERS			=	$(OBJ) $(SRC) $(INCLUDE)
INCLUDES		=	-I $(INCLUDE) -I ..

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
H_FILES				=	$(addprefix $(INCLUDE)/, $(SRC_H_FILES))
C_FILES				=	$(addprefix $(SRC)/, $(SRC_C_FILES))
O_FILES				=	$(addprefix $(OBJ)/, $(patsubst %.c, %.o, $(SRC_C_FILES)))

SOURCE_FILES		=	$(H_FILES) $(C_FILES)

# Target files (Object archive and H files)
TARGET_C_ARCHIVES	=	$(addprefix ../, $(C_ARCHIVES))
TARGET_H_FILES		=	$(addprefix ../, $(notdir $(H_FILES)))

# Colours for printouts
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
END				=	\033[0m

.PHONY: all
all: $(TARGET_H_FILES) $(TARGET_C_ARCHIVES)
	@echo -n ""

$(TARGET_H_FILES): $(H_FILES)
	@for file in $(H_FILES) ; do \
	    cp $$file ../ ; \
		echo "File $(YELLOW)$$file$(END) -> $(GREEN)../`basename $$file`$(END) copied!" ; \
	done

$(TARGET_C_ARCHIVES): $(C_ARCHIVES)
	@cp $(notdir $@) $@
	@echo "File $(YELLOW)$(notdir $@)$(END) -> $(GREEN)$@$(END) copied!"

$(C_ARCHIVES): $(O_FILES)
	@ar -rcs $@ $(O_FILES)

$(O_FILES): $(OBJ)/%.o: $(SRC)/%.c Prerequisites $(H_FILES)
	@$(CC) -c -o $@ $< $(C_FLAGS)
	@echo "    File $(YELLOW)$<$(END) -> $(GREEN)$@$(END) compiled!"

Prerequisites: $(H_FILES) Makefile | $(SOURCE_FILES)
	@touch Prerequisites
	@echo "$(YELLOW)Prerequisites are modified$(END)"

$(SOURCE_FILES): | $(FOLDERS)
	touch $@
	@echo "Source file $(GREEN)$@$(END) created (empty)!"

$(FOLDERS):
	mkdir $@

.PHONY: clean
clean:
	rm -f $(O_FILES)

.PHONY: fclean
fclean: clean
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
