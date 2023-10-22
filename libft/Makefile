# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/16 14:57:07 by sel-jama          #+#    #+#              #
#    Updated: 2023/07/08 08:36:10 by sel-jama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_isalpha.c ft_memchr.c ft_memset.c ft_strlen.c ft_toupper.c \
ft_atoi.c ft_isascii.c ft_memcmp.c ft_strchr.c ft_strncmp.c  \
ft_bzero.c ft_isdigit.c ft_memcpy.c ft_strlcat.c ft_strrchr.c \
ft_isalnum.c ft_isprint.c ft_memmove.c ft_strlcpy.c ft_tolower.c ft_strnstr.c \
ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_putchar_fd.c \
ft_putstr_fd.c ft_putendl_fd.c  ft_putnbr_fd.c ft_strmapi.c ft_striteri.c ft_split.c 

BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJS = ${SRCS:.c=.o}

BOBJS = ${BONUS:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

all: ${NAME}

${NAME}: ${OBJS}
	@ar rc ${NAME} ${OBJS}

bonus: ${BOBJS}
	@ar rc ${NAME} ${BOBJS}

clean:
	@rm -f ${OBJS} ${BOBJS}

fclean: clean
	@rm -f ${NAME}

re: fclean libft.a

.PHONY : clean fclean re
