# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 11:50:38 by jkauppi           #+#    #+#              #
#    Updated: 2021/11/04 15:22:42 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Input parameters

MK_SYSTEM			=	Makefile_System.mk
MK_SOURCE_FILES		=	Makefile_Source_Files.mk
MAKEFILES			=	$(MK_SYSTEM) $(MK_SOURCE_FILES)

include		$(MK_SYSTEM)
include		$(MK_SOURCE_FILES)

NAME1				=	libml.a
C_ARCHIVES			=	$(NAME1)

# Folders
OBJ					=	obj
SRC					=	src
INCLUDE				=	include
FOLDERS				=	$(OBJ) $(SRC) $(INCLUDE)
INCLUDES			=	-I $(INCLUDE) -I .. $(SYSTEM_INCLUDE)

# Compiler and linking parameters
CC					=	clang
C_FLAGS				=	-std=gnu17 -g -Wall -Wextra -Werror $(INCLUDES)
LD_FLAGS			=	$(D_ATTRIBUTES)

# Path folders for H, C and O files
H_FILES				=	$(addprefix $(INCLUDE)/, $(SRC_H_FILES))
C_FILES				=	$(addprefix $(SRC)/, $(SRC_C_FILES))
O_FILES				=	$(addprefix $(OBJ)/, $(patsubst %.c, %.o, $(SRC_C_FILES)))

# Target files (Object archive and H files)
TARGET_C_ARCHIVES	=	$(addprefix ../, $(C_ARCHIVES))
TARGET_H_FILES		=	$(addprefix ../, $(notdir $(H_FILES)))

.PHONY: all
all: $(SELF_SIGNED_CRT) $(TARGET_C_ARCHIVES) $(TARGET_H_FILES)
	@echo -n ""

$(TARGET_H_FILES): $(H_FILES) Makefile
	@for file in $(H_FILES) ; do \
	    cp $$file ../ ; \
		echo "File $(YELLOW)$$file$(END) -> $(GREEN)../`basename $$file`$(END) copied!" ; \
	done

$(TARGET_C_ARCHIVES): Makefile $(C_ARCHIVES) | prepare
ifneq ("$(wildcard $(notdir $@))","")
	@cp $(notdir $@) $@
	@echo "File $(YELLOW)$(notdir $@)$(END) -> $(GREEN)$@$(END) copied!"
endif

$(C_ARCHIVES): $(O_FILES)
ifneq (, $(O_FILES))
	@ar -rcs $@ $(O_FILES)
	@echo "    Archive file $(GREEN)$@$(END) created!"
endif

$(O_FILES): $(OBJ)/%.o: $(SRC)/%.c $(H_FILES) Makefile
	@$(CC) -c -o $@ $< $(C_FLAGS) $(LD_FLAGS)
	@echo "    File $(YELLOW)$<$(END) -> $(GREEN)$@$(END) compiled!"

.PHONY: prepare
prepare: $(FOLDERS) $(C_FILES)

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
