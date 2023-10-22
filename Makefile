# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/05 22:34:58 by sel-jama          #+#    #+#              #
#    Updated: 2023/10/21 00:19:58 by sel-jama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = parse/main.c parse/tokenise.c parse/syntax.c parse/expansion.c parse/expansion2.c parse/expansion3.c parse/expansion4.c parse/double_red.c\
	parse/parse.c parse/parse1.c parse/parse_utils.c parse/parse_utils2.c parse/parse_utils3.c parse/quotes.c parse/redirections.c\
	parse/redirections1.c parse/quotes1.c parse/quotes2.c parse/syntax1.c parse/tokenise1.c parse/tokenise2.c parse/expand_hdoc.c\
	parse/expand_hdoc1.c parse/expand_hdoc2.c parse/signals.c parse/quotes_utils.c parse/expaded_value.c\
	execution/execute/execute_cmd.c execution/execute/handling_pipe.c execution/builts/handling_b.c\
	execution/builts/cd.c execution/builts/env.c execution/builts/pwd.c execution/builts/load_env.c execution/builts/echo.c \
	execution/builts/export.c execution/builts/check_interput.c execution/builts/unset.c execution/builts/exit.c \
	execution/builts/cd_2.c execution/builts/ft_cd3.c execution/execute/handling_pipe2.c execution/execute/handling_pipe3.c execution/execute/handling_pipe4.c \
	execution/execute/execute_cmd2.c execution/execute/execute_cmd3.c execution/builts/cd_2v2.c execution/builts/export_v2.c execution/builts/export_v3.c \
	execution/builts/export_v4.c execution/builts/handling_b_v2.c execution/builts/load_env_v2.c parse/more_utils.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror

CC = cc

NAME = minishell

all : ${NAME}

${NAME} : ${OBJS}
	make -C libft/
	make bonus -C libft/
	${CC} ${CFLAGS} ${OBJS} libft/libft.a -o ${NAME} -lreadline -L ~/.brew/Cellar/readline/8.2.1/lib

clean :
	@rm -rf ${OBJS}
	@make clean -C libft/

fclean : clean
	@rm -rf ${NAME}
	@make fclean -C libft/

re : fclean all
