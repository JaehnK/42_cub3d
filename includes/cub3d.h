#ifndef CUB3D_H
#define CUB3D_H

# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define PLANE_X 0
# define PLANE_Y 0.66
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05
# define SCREEN_W 1280
# define SCREEN_H 720
# define TEX_W 64
# define TEX_H 64

typedef	struct	s_map_list t_map_list;

typedef	struct	s_map_list
{
	int			idx;
	char		*line;
	t_map_list	*next;
}	t_map_list;

typedef	struct	s_file
{
	char	*filename; // 파일이름
	char	*no_dir;	// 경로 북쪽
	char	*so_dir;	// 경로 남
	char	*we_dir;	//	경로 서
	char	*ea_dir;	// 경로 동
	char	*f_dir;	//	바닥색
	char	*c_dir;	//	천장 색
	char	**maparr;	//	 맵 배열
	int		map_width;	// 맵 가로
	int		map_height;	// 맵 세로
	double	pos_x;	// 캐릭 위치
	double	pos_y;	// 캐릭 위치
	int		pos_dir;	// 캐릭 방향 // E:1 W:2 S:3 N:4
	int		pos_dir_x; 	// 캐릭 시야
	int		pos_dir_y;	// 캐릭 시야	
	int		texture[8][TEX_H * TEX_W];
}	t_file;

typedef	struct s_img
{
	void	*img;
	int		*data;
	char	*addr;
	int 	size_l;
	int		bits_per_pixel;
	int		line_length;
	int		img_width;
	int		img_height;
	int		endian;
}	t_img;

typedef struct t_data
{
	int		**textures;
	int		ceiling_clr;
	int		floor_clr;
	int		buf_flag;
	int		**buf;
	void	*mlx;
	void	*win;
	t_img	img;
}	t_data;

typedef struct s_cub
{
	t_file	*file;
	t_data	*data;
}	t_cub;

int	ft_parse_file(int ac, char **av, t_file **f);
int	ft_check_empty_line(char *str);
int ft_has_dirs(t_file *f);
int	ft_parse_map(int fd, t_file **f);
int	ft_validate_map(t_file **f);

int	check_frontier(char **map, int i, int width);
int	check_inside_zero(char **map, int i, int j);
int	get_pos(char **map, int i, int j, t_file **f);

void	ft_read_cub_value(t_file **f, t_cub **cb);


void	ft_mlx_init(t_data *data);
void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
int     key_press(int keycode, t_cub *cub);

int     main_loop(t_cub **cub);


void	ft_split_free(char **arr);
void	ft_exit(char *msg, int exit_num, t_file **f);



#endif