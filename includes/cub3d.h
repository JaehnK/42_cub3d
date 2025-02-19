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
# define ROT_SPEED 0.1
# define texWidth 64
# define texHeight 64
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_ESC 65307
#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_RELEASE	3
#define X_EVENT_KEY_EXIT	17
#define KEY_PRESS_MASK	1L<<0
#define mapWidth 24
#define mapHeight 24

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
	double	plane_x;
    double	plane_y;
	int		map_width;	// 맵 가로
	int		map_height;	// 맵 세로
	double	pos_x;	// 캐릭 위치
	double	pos_y;	// 캐릭 위치
	int		pos_dir;	// 캐릭 방향 // E:1 W:2 S:3 N:4
	int		pos_dir_x; 	// 캐릭 시야
	int		pos_dir_y;	// 캐릭 시야	
}	t_file;

typedef struct s_img
{
    void    *img;           // MLX 이미지 포인터
    int     *data;          // 이미지 데이터 배열
    char    *addr;          // 픽셀 주소
	int 	size_l;
    int     line_length;    // 한 줄의 바이트 수
    int     bits_per_pixel; // bits per pixel
    int     endian;         // 엔디안
    int     img_width;      // 이미지 너비
    int     img_height;     // 이미지 높이
} t_img;

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

typedef struct s_ray_info {
    double pos_x; // posX
    double pos_y; // posY
    double dir_x; // dirX
    double dir_y; // dirY
    double plane_x; // plane_x
    double plane_y; // plane_y
    int     buf[SCREEN_HEIGHT][SCREEN_WIDTH];  // height, width를 매크로 상수로 변경
    int     **texture;
    double  move_speed; //move_speed
    double  rot_speed; //rot_speed
    int     **world_map;
    int     map_width;
    int     map_height;
} t_ray_info;

typedef struct s_cub {
    t_file      *file;
    t_data      *data;
    t_ray_info  ray;  // 레이캐스팅 정보 추가
} t_cub;

int		ft_parse_file(int ac, char **av, t_file **f);
int		ft_check_empty_line(char *str);
int 	ft_has_dirs(t_file *f);
int		ft_parse_map(int fd, t_file **f);
int		ft_validate_map(t_file **f);
// void load_texture(t_cub *cub);
int		check_frontier(char **map, int i, int width);
int		check_inside_zero(char **map, int i, int j);
int		get_pos(char **map, int i, int j, t_file **f);
void	ft_read_cub_value(t_file **f, t_cub **cub);

void	ft_mlx_init(t_data *data);
void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		key_press(int key, t_cub *cub);

int		main_loop(t_cub **cub);
int		init_world_map(t_cub *cub);
int 	init_ray_info(t_cub *cub);

void 	draw(t_cub *cub);
void 	calc(t_cub *cub);

void	ft_split_free(char **arr);
void	ft_exit(char *msg, int exit_num, t_file **f);


#endif
