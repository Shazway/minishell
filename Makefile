# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/23 18:58:48 by tmoragli          #+#    #+#              #
#    Updated: 2022/08/06 15:09:10 by mdkhissi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----------- EXECUTABLE -----------
NAME		=	minishell
DESCRIPTION =	Minishell

# ----------- COMPILER FLAGS -------
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror
LPFLAGS		=	-L$(LIBFT) -lft -lreadline

# ----------- INCLUDE --------------
INCLUDE		=	includes
INCLUDES	=	-I $(INCLUDE) -I $(LIBFT)

# ----------- FILES ----------------
SRC			=	./srcs
OBJ			=	./objs
LIBFT		=	./libft
SRCS		=	builtins/cd.c			\
				builtins/cd_utils.c		\
				builtins/echo.c			\
				builtins/env.c			\
				builtins/exit.c			\
				builtins/export.c		\
				builtins/export_utils.c	\
				builtins/pwd.c			\
				builtins/unset.c			\
				setup_redirections.c		\
				cmd.c					\
				execution.c				\
				main.c					\
				minishell.c				\
				redirections.c			\
				parsing.c				\
				signals.c				\
				unquote_split.c			\
				expand_variables.c		\
				utils.c					\
				quotes_parsing.c			\
				pipe_utils.c				\
				msh_utils.c				\
				cmd_utils.c				\
				heredoc.c				\
				str_arr_utils.c			\
				pre_parsing.c			\
				quotes_parsing_utils.c	\
				expand_utils.c			\
				redirections_utils.c		\
				builtins/cd_home.c		\
				arr_del_utils.c

OBJS		= $(patsubst %.c, $(OBJ)/%.o,$(SRCS))

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
			norminette $(INCLUDE)
	@echo "$(RED) =========> Checking the norminette............DONE √\n"

.PHONY: all clean fclean re norm