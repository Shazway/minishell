# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/23 18:58:48 by tmoragli          #+#    #+#              #
#    Updated: 2022/07/10 16:06:39 by tmoragli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----------- EXECUTABLE -----------
NAME		= minishell
DESCRIPTION = Minishell

# ----------- COMPILER FLAGS -------
CC			= clang
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g3
LPFLAGS		= -L$(LIBFT) -lft -lreadline

# ----------- INCLUDE --------------
INCLUDE		= includes
INCLUDES	= -I $(INCLUDE) -I $(LIBFT)

# ----------- FILES ----------------
SRC			= ./srcs
OBJ			= ./objs
LIBFT		= ./libft
SRCS		=	$(SRC)/builtins.c 		\
				$(SRC)/cd.c 			\
				$(SRC)/minishell.c		\
				$(SRC)/parsing.c		\
				$(SRC)/utils.c			\
				$(SRC)/unquote_split.c
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