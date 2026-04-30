# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: martimar <martimar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 15:20:49 by juetxeba          #+#    #+#              #
#    Updated: 2026/04/30 13:55:49 by juetxeba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC_DIR = srcs/
SRCS	= $(wildcard $(SRC_DIR)*.c)
OBJ_DIR = objs/
OBJECTS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -I include
LDLIBS = -lreadline
LDFLAGS = -L$(LIBFT_DIR) -lft


all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $@
	@echo "Executable $(NAME) created!"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) bonus

start:
	@mkdir -p include
	@mkdir -p srcs
	@mkdir -p objs
	@echo "Directories created"

moveS:
	@mv *.c* srcs

moveI:
	@mv *.h* include

redistribute: start moveI moveS

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm -f $(OBJECTS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
