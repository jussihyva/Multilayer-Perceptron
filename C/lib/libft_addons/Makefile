# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 11:50:38 by jkauppi           #+#    #+#              #
#    Updated: 2021/11/03 23:33:51 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Input parameters

include		mk_source_files.mk
include		mk_cert_variables.mk

OS				=	$(shell uname -s)
ifeq ($(OS), Darwin)
	D_ATTRIBUTES	=	-D DARWIN
	MAC_INCLUDES	=	-I $(HOME)/.brew/Cellar/openssl@1.1/1.1.1k/include
	MAC_INCLUDES	+=	-I $(HOME)/.brew/Cellar/openssl@1.1/1.1.1k/include
endif

NAME			=	libft_addons.a

# Folders
OBJ				=	obj
SRC				=	src
INCLUDE			=	include
FOLDERS			=	$(OBJ) $(SRC) $(INCLUDE)
INCLUDES		=	-I $(INCLUDE) -I ../libft -I ../libft_printf/include \
					$(MAC_INCLUDES)

# Compiler and linking parameters
CC				=	clang
C_FLAGS			=	-std=gnu17 -g -Wall -Wextra -Werror $(INCLUDES)
LD_FLAGS		=	$(D_ATTRIBUTES)

# C (Source code) and H (Header) files
TARGET_NAME		=	../$(NAME)

# Path folders for H, C, O and APP files
H_FILES			=	$(addprefix $(INCLUDE)/, $(SRC_H_FILES))
C_FILES			=	$(addprefix $(SRC)/, $(SRC_C_FILES))
O_FILES			=	$(addprefix $(OBJ)/, $(patsubst %.c, %.o, $(SRC_C_FILES)))

# Colours for printouts
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
END				=	\033[0m

.PHONY: all
all: $(SELF_SIGNED_CRT) $(TARGET_NAME)
	@echo "$(GREEN)Done!$(END)"

$(TARGET_NAME): $(FOLDERS) $(H_FILES) $(C_FILES) $(NAME)
	@cp $(notdir $@) $@
	@echo "$(GREEN)Done!$(END)"

$(NAME): $(O_FILES)
	@ar -rcs $(NAME) $(O_FILES)

$(O_FILES): $(OBJ)/%.o: $(SRC)/%.c $(H_FILES) Makefile
	$(CC) -c -o $@ $< $(C_FLAGS) $(LD_FLAGS)

$(FOLDERS):
	mkdir $@

$(C_FILES):
	touch $@

$(H_FILES):
	touch $@

.PHONY: clean
clean:
	rm -f $(O_FILES)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all

.PHONY: norm
norm:
ifeq ($(OS), Darwin)
	norminette-beta
else
	norminette
endif

include		mk_cert_actions.mk
