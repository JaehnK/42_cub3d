/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:38:34 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/19 15:38:35 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw(t_cub *cub)
{
	static int first_draw = 1;
	if (first_draw)
	{
		printf("Draw function called, using calc buffer\n");
		first_draw = 0;
	}

	// calc 함수의 버퍼를 화면에 그리기
	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{
			my_mlx_pixel_put(cub->data, x, y, cub->ray.buf[y][x]);
		}
	}
	
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img.img, 0, 0);
}

void calc(t_cub *cub)
{
static int first_calc = 1;
if (first_calc)
{
	printf("\n===== First Calc Call =====\n");
	printf("Player position: (%f, %f)\n", cub->ray.pos_x, cub->ray.pos_y);
	printf("Direction: (%f, %f)\n", cub->ray.dir_x, cub->ray.dir_y);
	printf("Camera plane: (%f, %f)\n", cub->ray.plane_x, cub->ray.plane_y);
	printf("Map dimensions: %d x %d\n", cub->ray.map_width, cub->ray.map_height);
	first_calc = 0;
}

for(int x = 0; x < SCREEN_WIDTH; x++)
{
	double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
	double raydir_x = cub->ray.dir_x + cub->ray.plane_x * cameraX;
	double rayDirY = cub->ray.dir_y + cub->ray.plane_y * cameraX;

	int mapX = (int)cub->ray.pos_x;
	int mapY = (int)cub->ray.pos_y;

	double deltaDistX = (raydir_x == 0) ? 1e30 : fabs(1 / raydir_x);
	double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

	double sideDistX;
	double sideDistY;
	
	int stepX = (raydir_x < 0) ? -1 : 1;
	int stepY = (rayDirY < 0) ? -1 : 1;

	if (raydir_x < 0)
		sideDistX = (cub->ray.pos_x - mapX) * deltaDistX;
	else
		sideDistX = (mapX + 1.0 - cub->ray.pos_x) * deltaDistX;
	if (rayDirY < 0)
		sideDistY = (cub->ray.pos_y - mapY) * deltaDistY;
	else
		sideDistY = (mapY + 1.0 - cub->ray.pos_y) * deltaDistY;

	int hit = 0;
	int side = 0;
	while (hit == 0)
	{
		int nextMapX = mapX;
		int nextMapY = mapY;
		
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			nextMapX = mapX + stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			nextMapY = mapY + stepY;
			side = 1;
		}
		
		if (nextMapX < 0 || nextMapX >= cub->ray.map_width || 
			nextMapY < 0 || nextMapY >= cub->ray.map_height)
		{
			hit = 1;
			break;
		}
		
		mapX = nextMapX;
		mapY = nextMapY;
		
		if (cub->ray.world_map[mapY][mapX] > 0)
			hit = 1;
	}

	double perpWallDist;
	if (side == 0)
		perpWallDist = (mapX - cub->ray.pos_x + (1 - stepX) / 2) / raydir_x;
	else
		perpWallDist = (mapY - cub->ray.pos_y + (1 - stepY) / 2) / rayDirY;

	int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

	int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (drawStart < 0) drawStart = 0;
	int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

	// 텍스처 계산
	double wallX;
	if (side == 0)
		wallX = cub->ray.pos_y + perpWallDist * rayDirY;
	else
		wallX = cub->ray.pos_x + perpWallDist * raydir_x;
	wallX -= floor(wallX);

	int texX = (int)(wallX * (double)texWidth);
	if (side == 0 && raydir_x > 0) texX = texWidth - texX - 1;
	if (side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

	// 텍스처 적용
	int texNum;
	if (side == 0)
		texNum = (raydir_x > 0) ? 0 : 1;  // east/west
	else
		texNum = (rayDirY > 0) ? 2 : 3;  // south/north

	// 천장
	for(int y = 0; y < drawStart; y++)
		cub->ray.buf[y][x] = cub->data->ceiling_clr;

	// 벽 (텍스처 적용)
	double step = 1.0 * texHeight / lineHeight;
	double texPos = (drawStart - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
	
	for(int y = drawStart; y < drawEnd; y++)
	{
		int texY = (int)texPos & (texHeight - 1);
		texPos += step;

		int color = cub->data->textures[texNum][texHeight * texY + texX];
		if (side == 1)
			color = (color >> 1) & 8355711;  // 어둡게
		cub->ray.buf[y][x] = color;
	}

	// 바닥
	for(int y = drawEnd; y < SCREEN_HEIGHT; y++)
		cub->ray.buf[y][x] = cub->data->floor_clr;
		//   cub->ray.buf[y][x] = 0x888888;
}
}


int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	cub->data = malloc(sizeof(t_data));
	cub->file = NULL;
	ft_mlx_init(cub->data);
	ft_parse_file(argc, argv, &(cub->file));
	if (init_world_map(cub))
	{
		printf("Error: World map initialization failed\n");
		return (-1);
	}
	if (init_ray_info(cub))
	{
		printf("Error: Ray info initialization failed\n");
		return (-1);
	}
	ft_read_cub_value(&(cub->file), &cub);
	mlx_loop_hook(cub->data->mlx, (void *)main_loop, &cub);
	mlx_hook(cub->data->win, X_EVENT_KEY_PRESS, KEY_PRESS_MASK, key_press, cub);
	mlx_hook(cub->data->win, X_EVENT_KEY_EXIT, 0, close_window, cub);
	mlx_loop(cub->data->mlx);
	return (0);
}
