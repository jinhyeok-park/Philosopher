# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 11:33:41 by jinhyeok          #+#    #+#              #
#    Updated: 2023/09/12 14:56:16 by jinhyeok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror 
NAME = philo_bonus
SOURCES = src/main.c \
		  src/checker.c \
		  src/error.c \
		  src/init.c \
		  src/waiter.c \
		  src/process.c \
		  src/utils.c \

INCLUDE = include

M_OBJ = $(SOURCES:.c=.o)

ifdef BONUS
	OBJECTS = $(B_OBJ)
else
	OBJECTS = $(M_OBJ)
endif

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -I $(INCLUDE) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re bonus