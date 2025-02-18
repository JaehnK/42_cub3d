/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:35:52 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/12 16:36:58 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct	s_ray
{
	double	cam_x;
	double	raydir_x;
	double	raydir_y;
	double	plane_x;
	double	plane_y;
	int		map_x;
	int		map_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		colour;
}	t_ray;

void	raycast_getdir(t_ray *ry, t_cub *cb)
{
	if (ry->raydir_x < 0)
	{
		ry->step_x = -1;
		ry->sidedist_x = (cb->file->pos_x - ry->map_x) * ry->deltadist_x;
	}
	else
	{
		ry->step_x = 1;
		ry->sidedist_x = (ry->map_x + 1.0 - cb->file->pos_x) * ry->deltadist_x;
	}
	if (ry->raydir_y < 0)
	{
		ry->step_y = -1;
		ry->sidedist_y = (cb->file->pos_y - ry->map_y) * ry->deltadist_y;
	}
	else
	{
		ry->step_y = 1;
		ry->sidedist_y = (ry->map_y + 1.0 - cb->file->pos_y) * ry->deltadist_y;
	}
}

void	ft_init_ray(int x, t_ray *ry, t_cub *cb)
{
	printf("pos_dir: %d %d\n", cb->file->pos_dir_x, cb->file->pos_dir_y);
	ry->cam_x = 2 * x / (double) SCREEN_W - 1;
	printf("plane: %f %f\n", ry->plane_x, ry->plane_y);
	ry->raydir_x = cb->file->pos_dir_x + ry->plane_x * ry->cam_x;
	ry->raydir_y = cb->file->pos_dir_y + ry->plane_y * ry->cam_x;
	printf("raydir: %f %f\n", ry->raydir_x, ry->raydir_y);
	ry->map_x = (int) cb->file->pos_x;
	ry->map_y = (int) cb->file->pos_y;
	ry->deltadist_x = (fabs(ry->raydir_x) < 0.0001) ? 1e30 : fabs(1 / ry->raydir_x);
    ry->deltadist_y = (fabs(ry->raydir_y) < 0.0001) ? 1e30 : fabs(1 / ry->raydir_y);
	printf("deltadist: %f %f\n", ry->deltadist_x, ry->deltadist_y);
	ry->hit = 0;
	raycast_getdir(ry, cb);
}

void	clean_buf(t_cub *cb)
{
	int i;

	i = 0;
	while (i < SCREEN_H)
		ft_memset(cb->data->buf[i++], 0, sizeof(int) * SCREEN_W);
}

void	dda(t_ray *ry, t_cub *cb)
{
	if (ry->sidedist_x < ry->sidedist_y)
	{
		ry->sidedist_x += ry->deltadist_x;
		ry->map_x += ry->step_x;
		ry->side = 0;
	}
	else
	{
		ry->sidedist_y += ry->deltadist_y;
		ry->map_y += ry->step_y;
		ry->side = 1;
	}
	if (cb->file->maparr[ry->map_x][ry->map_y] > '0')
		ry->hit = 1;
}

void	draw_on_buf(int x, t_ray *ry, t_cub *cb)
{
	int	y;

	ry->step = 1.0 * TEX_H /ry->line_height;
	ry->tex_pos = (ry->draw_start - SCREEN_H / 2 + ry->line_height / 2) * ry->step;
	y = ry->draw_start;
	// printf("y:%d drawend:%d\n", y, ry->draw_end);
	while (y < ry->draw_end)
	{
		ry->tex_y = (int) ry->tex_pos & (TEX_H - 1);
		ry->tex_pos += ry->step;
		ry->colour = cb->data->textures[ry->tex_num][TEX_H * ry->tex_y + ry->tex_x];
		if (ry->side == 1)
			ry->colour = (ry->colour >> 1) & 8355711;
		cb->data->buf[y][x] = ry->colour;
		cb->data->buf_flag = 1;
		y++;
	}
}

void render_walls(t_ray *ry, t_cub *cb)
{
    if (ry->side == 0)
        ry->perp_wall_dist = (ry->map_x - cb->file->pos_x + (1 - ry->step_x) / 2) / ry->raydir_x;
    else
        ry->perp_wall_dist = (ry->map_y - cb->file->pos_y + (1 - ry->step_y) / 2) / ry->raydir_y;
    if (ry->perp_wall_dist <= 0.0001)
		ry->perp_wall_dist = 0.0001;
	ry->line_height = (int)(SCREEN_H / ry->perp_wall_dist);
	if (ry->line_height > SCREEN_H * 10)  // 적절한 최대값 설정
		ry->line_height = SCREEN_H * 10;
	//printf("lineHeight %d perp %f", ry->line_height, ry->perp_wall_dist);
    ry->draw_start = -ry->line_height / 2 + SCREEN_H / 2;
    if (ry->draw_start < 0)
        ry->draw_start = 0;
    ry->draw_end = ry->line_height / 2 + SCREEN_H / 2;
    if (ry->draw_end >= SCREEN_H)
        ry->draw_end = SCREEN_H - 1;

    // Determine texture based on wall direction
    if (ry->side == 0)
    {
        if (ry->raydir_x > 0)
            ry->tex_num = 0; // EAST texture
        else
            ry->tex_num = 1; // WEST texture
    }
    else
    {
        if (ry->raydir_y > 0)
            ry->tex_num = 2; // SOUTH texture
        else
            ry->tex_num = 3; // NORTH texture
    }

    if (ry->side == 0)
        ry->wall_x = cb->file->pos_y + ry->perp_wall_dist * ry->raydir_y;
    else
        ry->wall_x = cb->file->pos_x + ry->perp_wall_dist * ry->raydir_x;
    ry->wall_x -= floor(ry->wall_x);

    ry->tex_x = (int)(ry->wall_x * (double)TEX_W);
    if (ry->side == 0 && ry->raydir_x > 0)
        ry->tex_x = TEX_W - ry->tex_x - 1;
    if (ry->side == 1 && ry->raydir_y < 0)
        ry->tex_x = TEX_W - ry->tex_x - 1;
}

void	raycast(t_cub *cb)
{
	int		x;
	t_ray	*ry;

	x = 0;
	ry = ft_calloc(sizeof(t_ray), 1);
	if (cb->data->buf_flag == 1)
		clean_buf(cb);
	ry->plane_x = PLANE_X;
	ry->plane_y = PLANE_Y;
	while (x < SCREEN_W)
	{
		ft_init_ray(x, ry, cb);
		while (ry->hit == 0)
			dda(ry, cb);
		render_walls(ry, cb);
		draw_on_buf(x, ry, cb);
		x++;	
	}
}

void	draw(t_cub *cub)
{
	int x;
	int	y;

	x = 0;
	y = 0;
	while (y < SCREEN_H)
	{
		x = 0;
		while (x < SCREEN_W)
		{
			//rintf("x: %d y: %d buf: %d\n", x, y, cub->data->buf[y][x]);
			// if (cub->data->buf[y][x] != 0)  // 버퍼에 값이 있는지 확인
            //    printf("Buffer at (%d,%d) = %d\n", x, y, cub->data->buf[y][x]);
			cub->data->img.data[y * SCREEN_W + x] = cub->data->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img.img, 0, 0);
}

int     main_loop(t_cub **cub)
{
    //mlx_hook((*cub)->data->win, 2, 1L<<0, key_press, *cub);
    raycast(*cub);
	draw(*cub);
    return (0);
}