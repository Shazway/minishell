# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/23 18:58:48 by tmoragli          #+#    #+#              #
#    Updated: 2022/07/28 19:27:57 by mdkhissi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----------- EXECUTABLE -----------
NAME		=	minishell
DESCRIPTION =	Minishell

# ----------- COMPILER FLAGS -------
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address 
LPFLAGS		=	-L$(LIBFT) -lft -lreadline

# ----------- INCLUDE --------------
INCLUDE		=	includes
INCLUDES	=	-I $(INCLUDE) -I $(LIBFT)

# ----------- FILES ----------------
SRC			=	./srcs
OBJ			=	./objs
LIBFT		=	./libft
SRCS		=	$(SRC)/builtins/cd.c		\
				$(SRC)/builtins/cd_utils.c	\
				$(SRC)/builtins/echo.c		\
				$(SRC)/builtins/env.c		\
				$(SRC)/builtins/exit.c		\
				$(SRC)/builtins/export.c	\
				$(SRC)/builtins/pwd.c		\
				$(SRC)/builtins/unset.c		\
				$(SRC)/setup_redirections.c	\
				$(SRC)/cmd.c				\
				$(SRC)/execution.c			\
				$(SRC)/main.c				\
				$(SRC)/minishell.c			\
				$(SRC)/redirections.c		\
				$(SRC)/parsing.c			\
				$(SRC)/signals.c			\
				$(SRC)/unquote_split.c		\
				$(SRC)/expand_variables.c	\
				$(SRC)/utils.c				\
				$(SRC)/quotes_parsing.c		\
				$(SRC)/pipe_utils.c			\
				$(SRC)/msh_utils.c			\
				$(SRC)/cmd_utils.c			\
				$(SRC)/find_path.c			\
				$(SRC)/heredoc.c			\
				$(SRC)/find_path_utils.c	\
				$(SRC)/str_arr_utils.c		\
				$(SRC)/pre_parsing.c

OBJS		= $(patsubst $(SRC)/%.c, $(OBJ)/%.o,$(SRCS))

# ----------- COLORS ---------------
BLACK		= \033[1;30m
RED			= \033[1;31m
GREEN		= \033[1;32m
PURPLE		= \033[1;35m
CYAN		= \033[1;36m
WHITE		= \033[1;37m
EOC			= \033[0;0m

# ----------- RULES ----------------
all			: $(NAME)
${NAME}		: $(OBJS)
	@echo "$(RED) =========> Compiling object files.............DONE √\n"
	@echo "$(WHITE)"
			$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LPFLAGS) -o $@
	@echo "$(RED) =========> Building $(DESCRIPTION).............DONE √\n"
	
$(OBJ)/%.o	: $(SRC)/%.c | $(OBJ) compiling
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

compiling	:
			@echo "$(WHITE)"

$(OBJ)		:
	@echo "$(PURPLE)"
			mkdir $@
			mkdir $@/builtins
	@echo "$(GREEN)"
			make bonus -C $(LIBFT)

clean		:
	@echo "$(PURPLE)"
			-rm -rf $(OBJ)
	@echo "$(RED) =========> Deleting object files.............DONE √\n"

fclean		: clean
	@echo "$(PURPLE)"
			-rm -f $(NAME)
	@echo "$(RED) =========> Deleting executable................DONE √\n"
	@echo "$(GREEN)"
			make fclean -C $(LIBFT)
	@echo "$(RED) =========> Cleaning libft.............DONE √\n"

re			: fclean all

norm		:
	@echo "$(BLACK)"
			norminette $(LIBFT)	
	@echo "$(CYAN)"
			norminette $(SRC) $(INCLUDE)
	@echo "$(RED) =========> Checking the norminette............DONE √\n"

.PHONY: all clean fclean re norm