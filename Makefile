# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/11 16:07:48 by sbakhit           #+#    #+#              #
#    Updated: 2024/09/11 17:21:24 by sbakhit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

HEADER = philo.h

FLAGS = -Wall -Wextra -Werror

SRC = main.c parsing.c utils.c program_init.c


all: $(NAME)

$(NAME): $(SRC) $(HEADER)
	@cc $(FLAGS) -o $(NAME) $(SRC)

clean:
	@rm -f $(NAME)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug