# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/14 21:27:41 by sbakhit           #+#    #+#              #
#    Updated: 2024/09/29 20:47:00 by sbakhit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

HEADER = philo.h

FLAGS = -Wall -Wextra -Werror -pthread -g3

SRC = main.c parsing.c utils.c program_init.c program.c monitor.c routine.c \
		eating_process.c routine_exec.c

INCLUDE = -pthread

CLANG = clang

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CLANG) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug

%.o: %.c $(HEADER)
	$(CLANG) $(INCLUDE) $(FLAGS) -c $< -o $(@)
