/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:23:30 by kjung             #+#    #+#             */
/*   Updated: 2025/02/22 20:39:11 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768
# define PLANE_X 0
# define PLANE_Y 0.66
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT	17
# define MAPWIDTH 24
# define MAPHEIGHT 24

typedef struct s_map_list	t_map_list;
typedef struct s_cub		t_cub;

typedef struct s_map_list
{
	int			idx;
	char		*line;
	t_map_list	*next;
}	t_map_list;

typedef struct s_file
{
	char	*filename;
	char	*no_dir;
	char	*so_dir;
	char	*we_dir;
	char	*ea_dir;
	char	*f_dir;
	char	*c_dir;
	char	**maparr;
	double	plane_x;
	double	plane_y;
	int		map_width;
	int		map_height;
	double	pos_x;
	double	pos_y;
	int		pos_dir;
	int		pos_dir_x;
	int		pos_dir_y;
}	t_file;

typedef struct s_img
{
	void	*img;
	int		*data;
	char	*addr;
	int		size_l;
	int		line_length;
	int		bits_per_pixel;
	int		endian;
	int		img_width;
	int		img_height;
}	t_img;

typedef struct t_data
{
	int		**textures;
	int		ceiling_clr;
	int		floor_clr;
	int		buf_flag;
	void	*mlx;
	void	*win;
	t_img	img;
}	t_data;

typedef struct s_ray_info
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		buf[SCREEN_HEIGHT][SCREEN_WIDTH];
	double	move_speed;
	double	rot_speed;
	int		**world_map;
	int		map_width;
	int		map_height;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	int		tex_x;
}	t_ray_info;

typedef struct s_cub
{
	t_file		*file;
	t_data		*data;
	t_ray_info	ray;
}	t_cub;

int		ft_parse_file(int ac, char **av, t_file **f);
int		ft_check_empty_line(char *str);
int		ft_has_dirs(t_file *f);
int		ft_parse_map(int fd, t_file **f);
int		ft_validate_map(t_file **f);
int		check_frontier(char **map, int i, int width);
int		check_inside_zero(char **map, int i, int j);
int		get_pos(char **map, int i, int j, t_file **f);
int		ft_read_cub_value(t_file **f, t_cub **cub);
void	ft_mlx_init(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		key_press(int key, t_cub *cub);
int		main_loop(t_cub **cub);
int		init_world_map(t_cub *cub);
int		init_ray_info(t_cub *cub);
void	ft_init_player_view(int x, t_cub *cub);
void	ft_hit_checker(t_cub *cub);
void	ft_calc_perp_wall_dist(t_cub *cub);
void	ft_calc_texture(t_cub *cub);
void	ft_adapt_texture(int x, t_cub *cub);
void	draw(t_cub *cub);
void	calc(t_cub *cub);
void	free_file_struct(t_file **file);
void	ft_free_cub(t_cub *cb);
void	ft_split_free(char **arr);
void	ft_exit(char *msg, int exit_num, t_file **f);
int		close_window(void *param);

#endif
