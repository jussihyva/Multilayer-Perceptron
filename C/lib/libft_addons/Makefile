# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 11:50:38 by jkauppi           #+#    #+#              #
#    Updated: 2021/11/11 19:12:45 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Input parameters

MK_SYSTEM			=	Makefile_System.mk
MK_SOURCE_FILES		=	Makefile_Source_Files.mk
MK_CERT_VAR			=	Makefile_Cert_Variables.mk
MK_CERT_ACTIONS		=	Makefile_Cert_Actions.mk
MAKEFILES			=	$(MK_SYSTEM) $(MK_SOURCE_FILES) $(MK_CERT_VAR) \
						$(MK_CERT_ACTIONS)

include		$(MK_SYSTEM)
include		$(MK_SOURCE_FILES)
include		$(MK_CERT_VAR)

NAME1				=	libft_addons.a
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

SOURCE_FILES		=	$(H_FILES) $(C_FILES)

# Target files (Object archive and H files)
TARGET_C_ARCHIVES	=	$(addprefix ../, $(C_ARCHIVES))
TARGET_H_FILES		=	$(addprefix ../, $(notdir $(H_FILES)))

.PHONY: all
all: $(SELF_SIGNED_CRT) $(TARGET_H_FILES) $(TARGET_C_ARCHIVES)
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
	@echo "    Archive file $(GREEN)$@$(END) created!"

$(O_FILES): $(OBJ)/%.o: $(SRC)/%.c Prerequisites $(H_FILES)
	@$(CC) -c -o $@ $< $(C_FLAGS) $(LD_FLAGS)
	@echo "    File $(YELLOW)$<$(END) -> $(GREEN)$@$(END) compiled!"

Prerequisites: $(H_FILES) Makefile $(MAKEFILES) | $(SOURCE_FILES) 
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

include		$(MK_CERT_ACTIONS)
