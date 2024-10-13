# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/13 17:33:20 by csalazar          #+#    #+#              #
#    Updated: 2024/10/13 19:04:17 by csalazar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
INCLUDE = include
CC = cc
FLAGS = -Wall -Werror -Wextra -I$(INCLUDE)
RM = rm -f
AR = ar -r
LIBFT = libft
SRC_DIR = src/
OBJ_DIR = obj/

SRC_FILES = ft_pipex.c ft_pipex_utils.c

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
				@make -C $(LIBFT)
				@cp $(LIBFT)/libft.a .
				@mv libft.a $(NAME)
				@$(AR) $(NAME) $(OBJS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
				$(CC) $(FLAGS) -c $< -o $@

clean:
				@$(RM) $(OBJS)
				@make clean -C $(LIBFT)

fclean: clean
				@$(RM) $(NAME)
				@$(RM) $(LIBFT)/libft.a

re: fclean all

.PHONY: all clean fclean re