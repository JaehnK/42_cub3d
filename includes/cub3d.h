#ifndef CUB3D_H
#define CUB3D_H

# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define SCREEN_WIDTH 768
# define SCREEN_HEIGHT 1024

typedef	struct	s_map_list t_map_list;

typedef	struct	s_map_list
{
	int			idx;
	char		*line;
	t_map_list	*next;
}	t_map_list;

typedef	struct	s_file
{
	char	*filename;
	char	*no_dir;
	char	*so_dir;
	char	*we_dir;
	char	*ea_dir;
	char	*f_dir;
	char	*c_dir;
	char	**maparr;
	int		map_width;
	int		map_height;
	float	pos_x;
	float	pos_y;
	int		pos_dir; // E:1 W:2 S:3 N:4
}	t_file;

typedef	struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*win;
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

void	ft_mlx_init(t_data *data);



void	ft_split_free(char **arr);
void	ft_exit(char *msg, int exit_num, t_file **f);



#endif