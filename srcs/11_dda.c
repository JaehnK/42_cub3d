/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:35:52 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/11 09:35:53 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    raycast(t_cub *cub)
{
    for(int x = 0; x < SCREEN_WIDTH; x++)
    {
        double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
        double rayDirX = cub->file->pos_dir_x + cub->file->plane_x * cameraX;
        double rayDirY = cub->file->pos_dir_y + cub->file->plane_y * cameraX;

        int mapX = (int)cub->file->pos_x;
        int mapY = (int)cub->file->pos_y;

        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);

        double sideDistX;
        double sideDistY;
        int stepX;
        int stepY;
        int hit = 0;
        int side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (cub->file->pos_x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - cub->file->pos_x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (cub->file->pos_y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - cub->file->pos_y) * deltaDistY;
        }

        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (cub->file->maparr[mapX][mapY] > 0)
                hit = 1;
        }

        double perpWallDist;
        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);

        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT)
            drawEnd = SCREEN_HEIGHT - 1;

        int color;
        switch(cub->file->maparr[mapX][mapY])
        {
            case 1:  color = 0xFF0000;  break; // 빨간색
            case 2:  color = 0x00FF00;  break; // 초록색
            case 3:  color = 0x0000FF;  break; // 파란색
            case 4:  color = 0xFFFFFF;  break; // 흰색
            default: color = 0xFFFF00;  break; // 노란색
        }

        if (side == 1)
            color = color / 2;

        for(int y = drawStart; y < drawEnd; y++)
        {
            my_mlx_pixel_put(cub->data, x, y, color);
        }
    }
    mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img->img, 0, 0);
}

int     main_loop(t_cub *cub)
{
    mlx_hook(cub->data->win, 2, 1L<<0, key_press, cub);
    raycast(cub);
    return (0);
}