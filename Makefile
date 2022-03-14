# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mverger <mverger@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/23 05:45:53 by jjaouen           #+#    #+#              #
#    Updated: 2022/03/13 18:28:18 by mverger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
GCCF = gcc -g #-Wall -Werror -Wextra
GREEN       = \033[32m
RED         = \033[31m
DEFAULT     = \033[37m
PATHOBJ = obj/
PATHSRC = src/
INCLUDE_PATH=include
DEP = Makefile src/$(INCLUDE_PATH)/pipex.h
SRC =   main.c ft_split.c generals_utils.c \
		init_struct.c cmd_process.c \
		test_infile_access.c memory.c
		
HEAD = -I ./src/$(INCLUDE_PATH)/ -I
OBJ = $(patsubst %.c,$(PATHOBJ)/%.o,$(SRC))

ifeq ($(shell uname),Darwin)
    ECHO    = echo
else
	ECHO    = echo
endif

all: $(NAME)

$(PATHOBJ):
	@mkdir -p obj

$(NAME): $(DEP) $(addprefix $(PATHSRC)/,$(SRC)) $(PATHOBJ) $(OBJ)
	@$(ECHO) "\r$(GREEN) The .o from $(NAME) are compiled.$(DEFAULT)"
	@$(GCCF) $(OBJ) -o $(NAME)
	@$(ECHO) "$(GREEN)$(NAME)$(DEFAULT) created."

$(PATHOBJ)/%.o: $(PATHSRC)/%.c
	@$(ECHO) "\r$(GREEN) Compiling $@                      \c\033[K"
	@$(GCCF) -c $< -o $@ $(HEAD)

clean:
	@$(ECHO) "All $(RED).o$(DEFAULT) are now deleted for $(NAME)."
	@make clean -C ./libft/
	@rm -rf $(PATHOBJ)

fclean: clean
	@$(ECHO) "$(RED)$(NAME)$(DEFAULT) is now deleted."
	@make fclean -C ./libft/
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re