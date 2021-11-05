# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 10:47:00 by jkauppi           #+#    #+#              #
#    Updated: 2021/11/05 12:20:00 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include Makefile_System.mk

# Application specific parameters
NAME1			=	training
NAME2			=	prediction
C_PROGRAMS		=	$(NAME1) $(NAME2)

# Input parameters

MK_SYSTEM			=	Makefile_System.mk
MK_CMD_ATTRS		=	Makefile_Cmd_Attributes.mk
MK_SOURCE_FILES		=	Makefile_Source_Files.mk
MAKEFILES			=	$(MK_SYSTEM) $(MK_CMD_ATTRS) $(MK_SOURCE_FILES)

include		$(MK_SYSTEM)
include		$(MK_CMD_ATTRS)
include		$(MK_SOURCE_FILES)

# Folders
LIB					=	lib
BIN					=	.
OBJ					=	obj
SRC					=	src
INCLUDE				=	include
TEST				=	test
FOLDERS				=	$(LIB) $(BIN) $(OBJ) $(SRC) $(INCLUDE) $(TEST)
INCLUDE_FILES		=	-I $(INCLUDE) -I $(LIB)

# C (Source code) and H (Header) files
LOCAL_LIB_FILES		=	$(addprefix $(LIB)/, $(LOCAL_LIBS))
LIB_FILES			=	$(addprefix -l , $(patsubst lib%.a, %, $(LOCAL_LIBS)))
LIB_FILES			+=	$(addprefix -l , $(patsubst lib%.a, %, $(GLOBAL_LIBS)))
LIB_FOLDERS			=	$(addprefix -L, $(GLOBAL_LIB_FOLDERS))

# Path folders for H, C, O and APP files
H_FILES				=	$(addprefix $(INCLUDE)/, $(patsubst %, %.h, $(C_PROGRAMS)))
H_FILES				+=	$(addprefix $(INCLUDE)/, $(SRC_H_FILES))
C_FILES				=	$(addprefix $(SRC)/, $(patsubst %, %.c, $(C_PROGRAMS)))
C_FILES				+=	$(addprefix $(SRC)/, $(SRC_C_FILES))
O_FILES				=	$(addprefix $(OBJ)/, $(patsubst %.c, %.o, $(SRC_C_FILES)))

# Compiler and linking parameters
CC					=	clang
C_FLAGS				=	-g -Wall -Wextra -Werror $(INCLUDE_FILES) $(SYSTEM_INCLUDE)
LD_FLAGS			=	-std=gnu17 -L$(LIB) $(LIB_FILES) $(LIB_FOLDERS)

ifeq ($(OS), Darwin)
	D_ATTRIBUTES	=	-D DARWIN
else
	D_ATTRIBUTES	=
endif
LD_FLAGS			+=	$(D_ATTRIBUTES)

SOURCE_FILES		=	$(H_FILES) $(C_FILES)

.PHONY: all
all: $(C_PROGRAMS)
	@echo -n ""

$(C_PROGRAMS): $(BIN)/%: $(SRC)/%.c Prerequisites $(H_FILES) $(LOCAL_LIB_FILES) $(O_FILES)
	@$(CC) -o $@ $< $(O_FILES) $(LD_FLAGS) $(C_FLAGS)
	@echo "Program $(GREEN)$@$(END) created!"

$(O_FILES): $(OBJ)/%.o: $(SRC)/%.c Prerequisites $(H_FILES) $(LOCAL_LIB_FILES)
	@$(CC) -c -o $@ $< $(C_FLAGS) $(D_ATTRIBUTES)
	@echo "File $(YELLOW)$<$(END) -> $(GREEN)$@$(END) compiled!"

Prerequisites: $(H_FILES) Makefile $(MAKEFILES) | $(SOURCE_FILES) Libraries ${LIB}/Makefile 
	@touch Prerequisites
	@echo "$(YELLOW)Prerequisites are modified$(END)"

$(SOURCE_FILES): | $(FOLDERS)
	touch $@
	@echo "Source file $(GREEN)$@$(END) created (empty)!"

$(FOLDERS):
	mkdir $@

.PHONY: Libraries
Libraries:
	@make --no-print-directory -C ${LIB} SHELL=$(SHELL)

${LIB}/Makefile:
	@echo "all:\n\t@echo -n \"\"" > $@

.PHONY: libraries_re
libraries_re:
	@make -C ${LIB} re

.PHONY: libraries_norm
libraries_norm:
	-@make -C ${LIB} norm

.PHONY: run
run: all
ifeq ($(OS), Darwin)
	$(CUR_DIR)/$(BIN)/$(NAME1) -S $(ITERATIONS) $(LEVEL) $(MODE) $(DATASET)
else
	$(CUR_DIR)/$(BIN)/$(NAME1) -S $(ITERATIONS) $(LEVEL) $(MODE) $(DATASET)
endif

.PHONY: run_leaks
run_leaks: all
ifeq ($(OS), Darwin)
	$(CUR_DIR)/$(BIN)/$(NAME1) -S $(ITERATIONS) $(LEVEL) -l $(MODE) $(DATASET)
else
	valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all \
	$(CUR_DIR)/$(BIN)/$(NAME1) -S $(ITERATIONS) $(LEVEL) $(MODE) $(DATASET)
endif

.PHONY: clean
clean:
	@make --no-print-directory -C ${LIB} clean
	rm -f $(O_FILES)

.PHONY: fclean
fclean: clean
	@make -C ${LIB} fclean
	rm -f $(BIN)/$(NAME1)
	rm -f $(BIN)/$(NAME2)

.PHONY: re
re: fclean all

.PHONY: norm
norm: libraries_norm
ifeq ($(OS), Darwin)
	norminette-beta
else
	norminette
endif
