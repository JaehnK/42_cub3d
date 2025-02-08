#ifndef CUB3D_H
#define CUB3D_H

# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

typedef	struct	s_file
{
	char	*filename;
	char	*no_dir;
	char	*so_dir;
	char	*we_dir;
	char	*ea_dir;
	char	*f_dir;
	char	*c_dir;
	char	**maplist;
	char	*escape;
}	t_file;

typedef	struct	s_map_list t_map_list;

typedef	struct	s_map_list
{
	int			idx;
	char		*line;
	t_map_list	*next;
}	t_map_list;

int	ft_parse_file(int ac, char **av, t_file **f);
int	ft_check_empty_line(char *str);
int ft_has_dirs(t_file *f);
int	ft_parse_map(int fd, t_file **f);


void	ft_split_free(char **arr);
void	ft_exit(char *msg, int exit_num, t_file **f);



#endif