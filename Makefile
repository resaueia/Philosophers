# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsaueia <rsaueia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/02 16:18:43 by rsaueia           #+#    #+#              #
#    Updated: 2025/01/02 16:43:37 by rsaueia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = 	main.c \
		utils.c \
		init.c \
		actions.c \
		libft.c

OBJS = $(SRCS:.c=.o)

GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
CYAN = \033[0;36m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo -e "$(BLUE)Compiling...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo -e "$(GREEN)Success: $(NAME) compiled successfully!$(RESET)"

%.o: %.c
	@echo -e "$(CYAN)Compiling $<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo -e "$(YELLOW)Extinguishing object files...$(RESET)"
	rm -f $(OBJS)

fclean: clean
	@echo -e "$(YELLOW)Removing $(NAME)...$(RESET)"
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re