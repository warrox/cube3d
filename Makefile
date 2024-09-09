# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 12:04:24 by cyferrei          #+#    #+#              #
#    Updated: 2024/09/09 13:25:48 by cyferrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
RM = rm -rf
XFLAGS = -Lmlx_linux -Imlx_linux -lX11 -lXext -lm -lz -Ofast
CFLAGS = -Wall -Wextra -Werror -g3
MLX_PATH = minilibx-linux/
LIBFT_CUB3D_PATH = libft_cub3D/
LIB_MLX = minilibx-linux/libmlx.a
LIBFT_CUB3D = libft_cub3D/cub3D.a

BOLD    = \e[1m
FADE    = \e[2m
ITA     = \e[3m
BLINK   = \e[5m
GREEN   = \e[38;5;76m
RED     = \e[38;5;196m
YELLOW  = \e[38;5;227m
ORANGE  = \e[38;5;208m
PURPLE  = \e[38;5;201m
LBLUE   = \e[38;5;45m
BLUE    = \e[38;5;27m
INDI    = \e[38;5;91m
SPINK   = \e[38;5;225m
PEACH   = \e[38;5;223m
GREY    = \e[38;5;254m
RESET   = \e[00m

SOURCE = ./src/


RAYCAST = $(addprefix raycast/, raycast.c raycast_util.c)
PARSING = $(addprefix parsing/, checker.c parser.c parser_utils.c free_handler.c error_handler.c error_handler_one.c cutter.c cutter_utils.c init.c)
GAME = $(addprefix $(SOURCE), $(PARSING) $(RAYCAST) main.c)

SRC = $(GAME)
OBJ = $(SRC:%.c=%.o)

all: minilibx-linux $(NAME)

$(NAME): $(OBJ)
	@echo "$(BOLD)Linking...$(RESET)"
	@make -sC $(MLX_PATH)
	@make -sC $(LIBFT_CUB3D_PATH)
	$(RM) $(NAME)
	make all -C ./libft_cub3D
	$(CC) $(CFLAGS) $(OBJ) $(LIB_MLX) $(XFLAGS) $(LIBFT_CUB3D) -o $(NAME)
	@echo "$(GREEN)Executable '$(NAME)' created successfully!$(RESET)"
	
minilibx-linux:
	git clone https://github.com/42Paris/minilibx-linux.git $@
	
%.o: %.c
	@echo "$(BOLD)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $(<:%.c=%.o)
	@echo "$(GREEN)$@ compiled successfully!$(RESET)"

clean:
	@echo "$(BOLD)Cleaning object files...$(RESET)"
	$(RM) $(OBJ)
	@make clean -C ./libft_cub3D
	@if [ -d "minilibx-linux" ]; then make clean -C minilibx-linux; fi
	@echo "$(GREEN)Object files cleaned successfully!$(RESET)"
	
fclean: clean
	@echo "$(BOLD)Cleaning executable...$(RESET)"
	$(RM) $(NAME)
	-make fclean -C ./libft_cub3D
	-$(RM) ./minilibx-linux  
	@echo "$(GREEN)Executable cleaned successfully!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
