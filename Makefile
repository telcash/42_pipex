# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/13 17:33:20 by csalazar          #+#    #+#              #
#    Updated: 2024/10/22 08:51:27 by csalazar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
INCLUDE = include
CC = cc
FLAGS = -g3 -Wall -Werror -Wextra -I$(INCLUDE)
RM = rm -f
AR = ar -r
LIBFT = libft
SRC_DIR = src/
OBJ_DIR = obj/

SRC_FILES = ft_pipex.c ft_pipex_utils.c ft_mod_split.c
SRC_FILES_B = ft_pipex_bonus.c ft_pipex_utils_bonus.c ft_pipex_utils.c ft_mod_split.c

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
SRCS_B = $(addprefix $(SRC_DIR), $(SRC_FILES_B))

OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
OBJS_B = $(addprefix $(OBJ_DIR), $(SRC_FILES_B:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
				@make -C $(LIBFT)
				@$(CC) $(FLAGS) $(OBJS) $(LIBFT)/libft.a -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
				$(CC) $(FLAGS) -c $< -o $@

bonus: 		 	$(OBJ_DIR) $(OBJS_B)
				@make -C $(LIBFT)
				@$(CC) $(FLAGS) $(OBJS_B) $(LIBFT)/libft.a -o $(NAME)

clean:
				@$(RM) $(OBJS)
				@make clean -C $(LIBFT)

fclean: clean
				@$(RM) $(NAME)
				@$(RM) $(LIBFT)/libft.a

re: fclean all

.PHONY: all clean fclean re