# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/23 18:58:48 by tmoragli          #+#    #+#              #
#    Updated: 2022/07/04 15:47:39 by tmoragli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINISHELL	=	minishell
SRCS		=	srcs/minishell.c								\
				srcs/parsing.c

INCLUDES	=	-Iincludes

OBJS		=	$(SRCS:.c=.o)
CC			=	gcc
RM			=	@rm -f

LD_FLAGS	=	libft/libft.a -fsanitize=address
FLAGS		=	-Wall -Werror -Wextra -lreadline $(INCLUDES) -g3
LIBFT		=	libft/libft.a
.c.o:
				$(CC) -c $< -o $(<:.c=.o) $(FLAGS)

all:			start_message $(MINISHELL)

$(MINISHELL):		$(LIBFT) $(OBJS) start_link
				$(CC) $(OBJS) $(FLAGS) -o $(MINISHELL) $(LD_FLAGS)
				@echo "\033[1;31mminishell\033[0m is ready to use!"

$(LIBFT):
				@make  -C libft -f Makefile

add_flag:
			$(eval FLAGS := -D BONUS=1)

clean:
#					@clear
					@make -s -C libft -f Makefile clean
					@echo "\033[0;33mCleaning \033[1;31mminishell\033[0;33m's objects\033[0m"
					$(RM) $(OBJS)

fclean:
					@make -s -C libft -f Makefile fclean
					@echo "\033[0;33mRemoving \033[1;31mminishell\033[0;33m.\033[0m"
					$(RM) $(MINISHELL) $(OBJS)
					$(RM) $(OBJS)
start_message:
#				@clear
				@echo "\033[0;31mMaking \033[1;31mminishell"
				@echo "\033[1;32mCompiling objects\033[0;32m"

start_link:
				@echo "\033[1;32mLinking all objects\033[0;32m"

re:				fclean all

.PHONY:			all clean fclean re