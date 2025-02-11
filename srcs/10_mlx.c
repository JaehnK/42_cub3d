/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:49:59 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/09 19:50:00 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB 3D");
	data->img->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->img->addr = mlx_get_data_addr(data->img->img, 
	 								&(data->img->bits_per_pixel), 
									&(data->img->line_length), 
									&(data->img->endian));
}

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->img->addr + (y * data->img->line_length + x * (data->img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int     key_press(int keycode, t_cub *cub)
{
    if (keycode == 53)  // ESC key
    {
        mlx_destroy_window(cub->data->mlx, cub->data->win);
        exit(0);
    }
    if (keycode == 13)  // W key
    {
        double newX = cub->file->pos_x + cub->file->pos_dir_x * MOVE_SPEED;
        double newY = cub->file->pos_y + cub->file->pos_dir_y * MOVE_SPEED;
        if (cub->file->maparr[(int)newX][(int)cub->file->pos_y] == 0)
            cub->file->pos_x = newX;
        if (cub->file->maparr[(int)cub->file->pos_x][(int)newY] == 0)
            cub->file->pos_y = newY;
    }
    if (keycode == 1)   // S key
    {
        double newX = cub->file->pos_x - cub->file->pos_dir_x * MOVE_SPEED;
        double newY = cub->file->pos_y - cub->file->pos_dir_y * MOVE_SPEED;
        if (cub->file->maparr[(int)newX][(int)cub->file->pos_y] == 0)
            cub->file->pos_x = newX;
        if (cub->file->maparr[(int)cub->file->pos_x][(int)newY] == 0)
            cub->file->pos_y = newY;
    }
    if (keycode == 2)   // D key
    {
        double oldDirX = cub->file->pos_dir_x;
        cub->file->pos_dir_x = cub->file->pos_dir_x * cos(-ROT_SPEED) - cub->file->pos_dir_y * sin(-ROT_SPEED);
        cub->file->pos_dir_y = oldDirX * sin(-ROT_SPEED) + cub->file->pos_dir_y * cos(-ROT_SPEED);
        double oldPlaneX = cub->file->plane_x;
        cub->file->plane_x = cub->file->plane_x * cos(-ROT_SPEED) - cub->file->plane_y * sin(-ROT_SPEED);
        cub->file->plane_y = oldPlaneX * sin(-ROT_SPEED) + cub->file->plane_y * cos(-ROT_SPEED);
    }
    if (keycode == 0)   // A key
    {
        double oldDirX = cub->file->pos_dir_x;
        cub->file->pos_dir_x = cub->file->pos_dir_x * cos(ROT_SPEED) - cub->file->pos_dir_y * sin(ROT_SPEED);
        cub->file->pos_dir_y = oldDirX * sin(ROT_SPEED) + cub->file->pos_dir_y * cos(ROT_SPEED);
        double oldPlaneX = cub->file->plane_x;
        cub->file->plane_x = cub->file->plane_x * cos(ROT_SPEED) - cub->file->plane_y * sin(ROT_SPEED);
        cub->file->plane_y = oldPlaneX * sin(ROT_SPEED) + cub->file->plane_y * cos(ROT_SPEED);
    }
    return (0);
}