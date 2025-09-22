# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: martimar <martimar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 15:20:49 by juetxeba          #+#    #+#              #
#    Updated: 2025/06/18 15:20:53 by martimar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SOURCES = \
		  minishell.c breakpipes.c cleaning_utils.c nodes.c \
		commander.c commander_utils2.c commander_utils.c env_export_commands.c \
		exit_command.c operatorImplementation.c operators.c pwd_command.c \
		unset_command.c cd_command.c expand_values.c echo_command.c\
		signal_handler.c nodes_utils.c nodes_utils2.c commander_utils3.c\
		utils.c utils2.c expand_values2.c utils3.c nodes_utils3.c\
		operators_utils.c export_command3.c operators_heredoc.c \
		commander_utils4.c expand_values3.c export_command2.c\

OBJECTS = $(SOURCES:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(LIBFT_DIR)
LDLIBS = -lreadline
LDFLAGS = -L$(LIBFT_DIR) -lft


all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus


%.o: %.c minishell.h
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
