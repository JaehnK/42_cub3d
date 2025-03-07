# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kjung <kjung@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/03 11:43:32 by jaehukim          #+#    #+#              #
#    Updated: 2025/02/26 18:28:08 by kjung            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
CFLAGS_DEBUG = -fsanitize=address
MAKE = make --no-print-directory
NAME = cub3D
LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft
MLX = ./minilibx-linux/libmlx_Linux.a
MLX_DIR = ./minilibx-linux/
MLX_M1 = ./minilibx_mms_20200219/

HEADR = ./includes/cub3d.h \

SRCS_DIR = ./srcs
OBJS_DIR = ./objs

SRCS =	00_main.c \
		01_parse_file.c \
		01-01_parse_file_utils.c \
		02_parse_map.c \
		02-01_parse_map_utils.c \
		03_validate_map.c \
		03-01_validate_map_utils.c \
		04_read_cub_value.c \
		10_mlx.c \
		11_mlx_keyhook.c \
		11-01_mlx_keyhook_arrow.c \
		20_main_loop.c \
		21_init_worldmap.c \
		22_init_ray_info.c \
		23_calcul.c \
		24_init_view.c \
		25_hit_checker.c \
		26_calc_perp_wall_dist.c \
		27_calc_texture.c \
		28_adapt_texture.c \
		29_draw.c \
		90_mlx_destories.c \
		99_free_handle.c


SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS := $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))
OBJS_DEBUG := $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%_debug.o,$(SRCS))

all: $(OBJS_DIR) $(NAME)

debug: CFLAGS += $(CFLAGS_DEBUG)

debug: $(OBJS_DIR) $(OBJS_DEBUG) $(LIBFT)
	@make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) -L$(MLX_DIR) -L$(LIBFT_DIR) -o $(NAME) -lmlx_Linux -lXext -lX11 -lm -lz $(LIBFT)
	@echo "cub3D (Debug version) is ready!"

$(NAME): $(OBJS) $(LIBFT)
	@make -C $(MLX_DIR)
	@$(CC) $(CFLAGS) $(OBJS) -L$(MLX_DIR) -L$(LIBFT_DIR) -o $(NAME) -lmlx_Linux -lXext -lX11 -lm -lz $(LIBFT)
	@echo "cub3D is ready!"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADR) | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I./includes -c $< -o $@

$(OBJS_DIR)/%_debug.o: $(SRCS_DIR)/%.c $(HEADR) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) -I./includes -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@rm -rf $(OBJS_DIR)
	@echo "Cleaning..."

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "Full cleaning..."

re: fclean all

.PHONY: all clean fclean re
