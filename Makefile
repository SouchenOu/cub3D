# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souchen <souchen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/21 13:19:25 by yismaili          #+#    #+#              #
#    Updated: 2022/11/12 13:26:06 by souchen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m
BBlue=\033[0;34m
BYellow=\033[1;33m
CC = gcc
FLAGS = -g -Wall -Werror -Wextra -g #-fsanitize=address
framework= -framework OpenGL -framework AppKit 
RM = rm -rf

FILES = rsc/read_map.c  rsc/main.c rsc/errors_handling.c raycaster/draw_map.c  rsc/find_pos_player.c rsc/wall_cordinate.c  rsc/func_math.c
 

OBJ_FILES= $(FILES:.c=.o)

MSG = Everything is fcleaned!
HEADER = ./include/cub3D.h
CREATER = yismaili && souchen
LIBFT = libft/libft.a
NAME = cub3D


all : $(NAME)
		@echo "$(GREEN)BY $(RED)$(CREATER)"

$(NAME) : $(OBJ_FILES) $(LIBFT)
	$(CC) $(OBJ_FILES) -lmlx  $(framework) $(LIBFT) $(FLAGS) -o $(NAME)
	
%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -o $@ -c $<
	@echo $(HOME)
	@echo "$(GREEN)COMPILING$(RESET) $<"

$(LIBFT):
	make -C libft

clean:
	$(RM) $(OBJ_FILES)
	@make fclean -C libft

fclean: clean
	$(RM) $(NAME)
	@make fclean -C libft
	@echo "$(RED) $(MSG) $(RESET)"

re: fclean clean all