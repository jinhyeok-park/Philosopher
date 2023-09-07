# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinhyeok <jinhyeok@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/21 19:16:02 by jinhyeok          #+#    #+#              #
#    Updated: 2023/09/07 11:23:25 by jinhyeok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
SOURCES = src/error.c \
		  src/main.c \
		  src/checker.c \
		  src/free.c \
		  src/thread.c \
		  src/get_time.c \
		  src/philo_utils.c\
		  src/philo_init.c
B_SOURCES =
INCLUDE = include

M_OBJ = $(SOURCES:.c=.o)
B_OBJ = $(B_SOURCES:.c=.o)

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

bonus:
	make BONUS=1 all

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
