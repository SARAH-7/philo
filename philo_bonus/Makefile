# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 18:38:30 by sbakhit           #+#    #+#              #
#    Updated: 2024/10/03 14:22:32 by sbakhit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

HEADER = philo_bonus.h

FLAGS = -Wall -Wextra -Werror -pthread

SRC = main_bonus.c parsing_bonus.c utils_bonus.c program_init_bonus.c program_bonus.c \
		monitor_bonus.c routine_bonus.c routine_exec_bonus.c 

INCLUDE = -pthread

CC = cc

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug

%.o: %.c $(HEADER)
	$(CC) $(INCLUDE) $(FLAGS) -c $< -o $(@)
