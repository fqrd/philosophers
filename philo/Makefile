# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 18:52:28 by fcaquard          #+#    #+#              #
#    Updated: 2022/02/19 19:40:16 by fcaquard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = philo
SRCS = \
	ft_atoi.c			\
	preparation.c		\
	activities.c		\
	main.c				\
	list.c				\
	time.c				\
	runtime.c			\
	cleaner.c			\

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -pthread -o $(NAME)

clean:
	rm -f ./*.o

fclean: clean
	rm ./$(NAME)

re: fclean all