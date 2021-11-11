# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 09:54:35 by jkauppi           #+#    #+#              #
#    Updated: 2021/11/11 19:30:37 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS			=	$(shell uname -s)
CUR_DIR		=	$(abspath .)

ifeq ($(OS), Darwin)
	SHELL				=	zsh
endif

NAME1			=	libft.a
C_ARCHIVES		=	$(NAME1)

# Folders
LIB				=	.
OBJ				=	obj
SRC				=	.
INCLUDE			=	.
FOLDERS			=	$(OBJ)
INCLUDES		=	-I $(INCLUDE)

# Compiler and linking parameters
CC				=	clang
C_FLAGS			=	-fPIE -std=gnu17 -g -Wall -Wextra -Werror $(INCLUDES)

# C (Source code) and H (Header) files
SRC_C_FILES		=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
					ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c \
					ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c \
					ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c \
					ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
					ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c \
					ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
					ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
					ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c \
					ft_putstr.c ft_putnbr.c ft_putchar_fd.c ft_putendl.c ft_putstr_fd.c \
					ft_putendl_fd.c ft_putnbr_fd.c \
					ft_lstnew.c ft_lstdelone.c ft_lstdel.c \
					ft_lstadd.c ft_lstadd_e.c ft_lstiter.c ft_lstmap.c \
					ft_isupper.c ft_islower.c ft_isspace.c \
					ft_get_fd_buf.c ft_get_next_line.c \
					ft_step_args.c ft_abs.c

SRC_H_FILES		=	libft.h

# Path folders for H, C, O and APP files
H_FILES			=	$(addprefix $(INCLUDE)/, $(SRC_H_FILES))
C_FILES			=	$(addprefix $(SRC)/, $(SRC_C_FILES))
O_FILES			=	$(addprefix $(OBJ)/, $(patsubst %.c, %.o, $(SRC_C_FILES)))

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

.PHONY: bonus
bonus: all

.PHONY: norm
norm:
ifeq ($(OS), Darwin)
	norminette
else
	norminette
endif
