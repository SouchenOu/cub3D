# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/21 13:19:25 by yismaili          #+#    #+#              #
#    Updated: 2022/11/23 22:58:23 by yismaili         ###   ########.fr        #
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

FILES = rsc/read_map.c  rsc/main.c rsc/errors_handling.c raycaster/draw_map.c  raycaster/raycasting.c raycaster/randeringWall.c 

OBJ_FILES= $(FILES:.c=.o)

MSG = Everything is fcleaned!
HEADER = ./include/cub3D.h
CREATER = #yismaili && souchen
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