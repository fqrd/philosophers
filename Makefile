# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 18:52:28 by fcaquard          #+#    #+#              #
#    Updated: 2021/12/26 14:06:24 by fcaquard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = philo
SRCS = \
	ft_atoi.c		\
	ft_itoa.c	\
	activities.c	\
	circle.c		\

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lbsd -o $(NAME)

clean:
	rm -f ./*.o

fclean: clean
	rm ./$(NAME)

re: fclean all