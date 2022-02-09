# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 18:52:28 by fcaquard          #+#    #+#              #
#    Updated: 2022/02/09 22:00:46 by fcaquard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = philo
SRCS = \
	ft_atoi.c		\
	ft_itoa.c		\
	activities.c	\
	main.c			\
	message.c		\
	list.c			\
	verifications.c	\
	time.c			\
	runtime.c			\
	numbers.c			\

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -pthread -lbsd -o $(NAME)

clean:
	rm -f ./*.o

fclean: clean
	rm ./$(NAME)

re: fclean all