SRCS_MEM	=	mem_fct/ft_memset.c mem_fct/ft_bzero.c mem_fct/ft_memcpy.c mem_fct/ft_memccpy.c mem_fct/ft_memmove.c mem_fct/ft_memchr.c mem_fct/ft_memcmp.c
SRCS_STR	=	str_fct/ft_strchr.c str_fct/ft_strdup.c str_fct/ft_strrchr.c str_fct/ft_strncmp.c str_fct/ft_strlcpy.c str_fct/ft_strlcat.c str_fct/ft_strnstr.c str_fct/ft_strlen.c str_fct/ft_error.c
SRCS_PUTFD	=	fd_fct/ft_putchar_fd.c fd_fct/ft_putstr_fd.c fd_fct/ft_putendl_fd.c fd_fct/ft_putnbr_fd.c
SRCS_IS		=	is_fct/ft_isalpha.c is_fct/ft_isdigit.c is_fct/ft_isalnum.c is_fct/ft_isascii.c is_fct/ft_isprint.c is_fct/ft_toupper.c is_fct/ft_tolower.c is_fct/ft_isblank.c
SRCS_TO		=	other/ft_atoi.c other/ft_itoa.c 
SRCS_MALLOC	=	mem_fct/ft_calloc.c mem_fct/ft_substr.c mem_fct/ft_strjoin.c mem_fct/ft_strtrim.c mem_fct/ft_split.c mem_fct/ft_strmapi.c mem_fct/ft_malloc.c mem_fct/ft_free_tab.c
SRCS_PRINTF =	ft_printf/ft_printf.c ft_printf/ft_parsing.c ft_printf/ft_putnbr_base.c ft_printf/ft_putnbr_base_2.c ft_printf/ft_hex.c ft_printf/ft_u.c ft_printf/ft_d_i.c ft_printf/ft_utils.c ft_printf/ft_p.c ft_printf/ft_s.c
SRCS_LST	=	lst_fct/ft_lstnew.c lst_fct/ft_lstadd_front.c lst_fct/ft_lstsize.c lst_fct/ft_lstlast.c lst_fct/ft_lstadd_back.c lst_fct/ft_lstdelone.c lst_fct/ft_lstclear.c lst_fct/ft_lstiter.c lst_fct/ft_lstmap.c
SRCS_GNL	=	get_next_line/get_next_line.c
SRCS		=	${SRCS_MEM} ${SRCS_STR} ${SRCS_PUTFD} ${SRCS_IS} ${SRCS_TO} ${SRCS_MALLOC} ${SRCS_LST} ${SRCS_PRINTF} ${SRCS_GNL}

OBJS		=	${SRCS:.c=.o}

CC			=	gcc
RM			=	rm -f
NAME		=	libft.a

FLAGS		=	-Wall -Werror -Wextra -Ift_printf -Iget_next_line -I./

.c.o:
			${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			ar rc ${NAME} ${OBJS}
			ranlib ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re