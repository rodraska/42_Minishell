# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/10 16:23:51 by rreis-de          #+#    #+#              #
#    Updated: 2023/04/19 17:01:25 by rreis-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

LDFLAGS = -lreadline

RM = rm -f

SRCS = mini.c \
		exec.c \
		builtin.c \
		utils.c \
		token_utils.c \
		env_var_utils.c \
		env_var_utils2.c \
		cmd_utils.c \
		path.c \
		ft_split.c
		
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re