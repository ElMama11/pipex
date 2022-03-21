# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/20 14:44:07 by mverger           #+#    #+#              #
#    Updated: 2022/03/20 17:24:02 by mverger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAMEBONUS = pipex_bonus
GCCF = gcc -g #-Wall -Werror -Wextra
GREEN       = \033[32m
RED         = \033[31m
DEFAULT     = \033[37m
PATHOBJ = obj/
PATHOBJBONUS = objbonus/
PATHSRC = src/
PATHSRCBONUS = bonus/
INCLUDE_PATH=include
DEP = Makefile src/$(INCLUDE_PATH)/pipex.h
SRC =   main.c ft_split.c generals_utils.c \
		init_struct.c cmd_process.c \
		test_infile_access.c memory.c

SRCBONUS =	cmd_process_bonus.c ft_split_bonus.c generals_utils_bonus.c \
			get_next_line_bonus.c get_next_line_utils_bonus.c here_doc_bonus.c \
			init_struct_bonus.c main_bonus.c memory_bonus.c test_infile_access_bonus.c
		
HEAD = -I ./src/$(INCLUDE_PATH)/ -I
OBJ = $(patsubst %.c,$(PATHOBJ)/%.o,$(SRC))

DEPBONUS = Makefile bonus/$(INCLUDE_PATH)/pipex_bonus.h
HEADBONUS= -I ./bonus/$(INCLUDE_PATH)/ -I
OBJBONUS= $(patsubst %.c,$(PATHOBJBONUS)/%.o,$(SRCBONUS))

ifeq ($(shell uname),Darwin)
    ECHO    = echo
else
	ECHO    = echo
endif

all: $(NAME)

bonus: $(NAMEBONUS)

$(PATHOBJ):
	@mkdir -p obj

$(PATHOBJBONUS):
	@mkdir -p objbonus
	
$(NAME): $(DEP) $(addprefix $(PATHSRC)/,$(SRC)) $(PATHOBJ) $(OBJ)
	@$(ECHO) "\r$(GREEN) The .o from $(NAME) are compiled.$(DEFAULT)"
	@$(GCCF) $(OBJ) -o $(NAME)
	@$(ECHO) "$(GREEN)$(NAME)$(DEFAULT) created."

$(PATHOBJ)/%.o: $(PATHSRC)/%.c
	@$(ECHO) "\r$(GREEN) Compiling $@                      \c\033[K"
	@$(GCCF) -c $< -o $@ $(HEAD)

$(NAMEBONUS): $(DEPBONUS) $(addprefix $(PATHSRCBONUS)/,$(SRCBONUS)) $(PATHOBJBONUS) $(OBJBONUS)
	@$(ECHO) "\r$(GREEN) The .o from $(NAMEBONUS) are compiled.$(DEFAULT)"
	@$(GCCF) $(OBJBONUS) -o $(NAMEBONUS)
	@$(ECHO) "$(GREEN)$(NAMEBONUS)$(DEFAULT) created."

$(PATHOBJBONUS)/%.o: $(PATHSRCBONUS)/%.c
	@$(ECHO) "\r$(GREEN) Compiling $@                      \c\033[K"
	@$(GCCF) -c $< -o $@ $(HEADBONUS)

clean:
	@$(ECHO) "All $(RED).o$(DEFAULT) are now deleted for $(NAME)."
	@rm -rf $(PATHOBJ)
	@rm -rf $(PATHOBJBONUS
	)

fclean: clean
	@$(ECHO) "$(RED)$(NAME)$(DEFAULT) is now deleted."
	@rm -rf $(NAME)
	@rm -rf $(NAMEBONUS)

re: fclean all

.PHONY: all clean fclean re bonus