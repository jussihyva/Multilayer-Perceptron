# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 10:47:00 by jkauppi           #+#    #+#              #
#    Updated: 2021/11/03 11:58:09 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include Makefile_System.mk

# Application specific parameters
C_PROGRAMS		=	training prediction

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
DOC					=	doc
FOLDERS				=	$(LIB) $(BIN) $(OBJ) $(SRC) $(INCLUDE) $(TEST) $(DOC)
INCLUDE_FILES		=	-I $(INCLUDE) -I $(LIB)

# C (Source code) and H (Header) files
LOCAL_LIB_FILES		=	$(addprefix $(LIB)/, $(LOCAL_LIBS))
LIB_FILES			=	$(addprefix -l , $(patsubst lib%.a, %, $(LOCAL_LIBS)))
LIB_FILES			+=	$(addprefix -l , $(patsubst lib%.a, %, $(GLOBAL_LIBS)))
LIB_FOLDERS			=	$(addprefix -L, $(GLOBAL_LIB_FOLDERS))

# Path folders for H, C, O and APP files
H_FILES				=	$(addprefix $(INCLUDE)/, $(SRC_H_FILES))
H_FILES				+=	$(addprefix $(INCLUDE)/, $(C_PROGRAMS).h)
C_FILES				=	$(addprefix $(SRC)/, $(SRC_C_FILES))
O_FILES				=	$(addprefix $(OBJ)/, $(patsubst %.c, %.o, $(SRC_C_FILES)))
# APP_FILES			=	$(addprefix $(BIN)/, $(NAMES))
C_PROGRAM_FILES		=	$(addprefix $(SRC)/, $(patsubst %, %.c, $(C_PROGRAMS)))

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

.PHONY: all
all: $(C_PROGRAMS)

$(C_PROGRAMS): $(BIN)/%: $(SRC)/%.c $(H_FILES) $(O_FILES) | prepare
	$(CC) -o $@ $< $(O_FILES) $(LD_FLAGS) $(C_FLAGS)
	@echo "Program $(GREEN)$@$(END) created!"

$(O_FILES): $(OBJ)/%.o: $(SRC)/%.c $(H_FILES) Makefile $(MAKEFILES) $(LOCAL_LIB_FILES)
	@$(CC) -c -o $@ $< $(C_FLAGS) $(D_ATTRIBUTES)
	@echo "File $(YELLOW)$<$(END) -> $(GREEN)$@$(END) compiled!"

.PHONY: prepare
prepare: $(FOLDERS) $(H_FILES) $(C_PROGRAM_FILES) $(C_FILES) ${LIB}/Makefile libraries

$(FOLDERS):
	mkdir $@

$(C_PROGRAM_FILES):
	touch $@

$(C_FILES):
	touch $@

$(H_FILES):
	touch $@

.PHONY: libraries
libraries:
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
	$(CUR_DIR)/$(BIN)/$(NAME) -S $(ITERATIONS) $(LEVEL) $(MODE) $(DATASET)
else
	$(CUR_DIR)/$(BIN)/$(NAME) -S $(ITERATIONS) $(LEVEL) $(MODE) $(DATASET)
endif

.PHONY: run_leaks
run_leaks: all
ifeq ($(OS), Darwin)
	$(CUR_DIR)/$(BIN)/$(NAME) -S $(ITERATIONS) $(LEVEL) -l $(MODE) $(DATASET)
else
	valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all \
	$(CUR_DIR)/$(BIN)/$(NAME) -S $(ITERATIONS) $(LEVEL) $(MODE) $(DATASET)
endif

.PHONY: clean
clean:
	@make --no-print-directory -C ${LIB} clean
	rm -f $(O_FILES)

.PHONY: fclean
fclean: clean
	@make -C ${LIB} fclean
	rm -f $(BIN)/$(NAME)

.PHONY: re
re: fclean all

.PHONY: norm
norm: libraries_norm
ifeq ($(OS), Darwin)
	norminette-beta
else
	norminette
endif
