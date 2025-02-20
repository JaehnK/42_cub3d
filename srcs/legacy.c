/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:38:34 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/20 16:36:49 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//void draw(t_cub *cub)
//{
//	int	i;
//	int	j;

//	i = 0;
//	while (i < SCREEN_HEIGHT)
//	{
//		j = 0;
//		while (j < SCREEN_WIDTH)
//		{
//			my_mlx_pixel_put(cub->data, j, i, cub->ray.buf[i][j]);
//			j++;
//		}
//		i++;
//	}
//	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img.img, 0, 0);
//}

//void calc(t_cub *cub)
//{
	
//	for(int x = 0; x < SCREEN_WIDTH; x++)
//	{
//		// 1번: init_player_view
//		double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
//		double raydir_x = cub->ray.dir_x + cub->ray.plane_x * camera_x;
//		double raydir_y = cub->ray.dir_y + cub->ray.plane_y * camera_x;

//		int map_x = (int)cub->ray.pos_x;
//		int map_y = (int)cub->ray.pos_y;

//		double delta_dist_x = (raydir_x == 0) ? 1e30 : fabs(1 / raydir_x);
//		double delta_dist_y = (raydir_y == 0) ? 1e30 : fabs(1 / raydir_y);

//		double side_dist_x;
//		double side_dist_y;
		
//		int step_x = (raydir_x < 0) ? -1 : 1;
//		int step_y = (raydir_y < 0) ? -1 : 1;

//		if (raydir_x < 0)
//			side_dist_x = (cub->ray.pos_x - map_x) * delta_dist_x;
//		else
//			side_dist_x = (map_x + 1.0 - cub->ray.pos_x) * delta_dist_x;
//		if (raydir_y < 0)
//			side_dist_y = (cub->ray.pos_y - map_y) * delta_dist_y;
//		else
//			side_dist_y = (map_y + 1.0 - cub->ray.pos_y) * delta_dist_y;

		
//		int hit = 0;
//		int side = 0;
//		while (hit == 0)
//		{
//			// 2, hit checker
//			int next_map_x = map_x;
//			int next_map_y = map_y;
			
//			if (side_dist_x < side_dist_y)
//			{
//				side_dist_x += delta_dist_x;
//				next_map_x = map_x + step_x;
//				side = 0;
//			}
//			else
//			{
//				side_dist_y += delta_dist_y;
//				next_map_y = map_y + step_y;
//				side = 1;
//			}
			
//			if (next_map_x < 0 || next_map_x >= cub->ray.map_width || 
//				next_map_y < 0 || next_map_y >= cub->ray.map_height)
//			{
//				hit = 1;
//				break;
//			}
			
//			map_x = next_map_x;
//			map_y = next_map_y;
			
//			if (cub->ray.world_map[map_y][map_x] > 0)
//				hit = 1;
//		}

//		// 3. calcul - perp-wall-dist
//		double perp_wall_dist;
//		if (side == 0)
//			perp_wall_dist = (map_x - cub->ray.pos_x + (1 - step_x) / 2) / raydir_x;
//		else
//			perp_wall_dist = (map_y - cub->ray.pos_y + (1 - step_y) / 2) / raydir_y;

//		int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);

//		int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
//		if (draw_start < 0) draw_start = 0;
//		int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
//		if (draw_end >= SCREEN_HEIGHT) draw_end = SCREEN_HEIGHT - 1;

//		// 텍스처 계산
//		double wall_x;
//		if (side == 0)
//			wall_x = cub->ray.pos_y + perp_wall_dist * raydir_y;
//		else
//			wall_x = cub->ray.pos_x + perp_wall_dist * raydir_x;
//		wall_x -= floor(wall_x);

//		int tex_x = (int)(wall_x * (double)texWidth);
//		if (side == 0 && raydir_x > 0) tex_x = texWidth - tex_x - 1;
//		if (side == 1 && raydir_y < 0) tex_x = texWidth - tex_x - 1;

//		// 텍스처 적용
//		int tex_num;
//		if (side == 0)
//			tex_num = (raydir_x > 0) ? 0 : 1;  // east/west
//		else
//			tex_num = (raydir_y > 0) ? 2 : 3;  // south/north

//		// 천장
//		for(int y = 0; y < draw_start; y++)
//			cub->ray.buf[y][x] = cub->data->ceiling_clr;

//		// 벽 (텍스처 적용)
//		double step = 1.0 * texHeight / line_height;
//		double tex_pos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;
		
//		for(int y = draw_start; y < draw_end; y++)
//		{
//			int tex_y = (int)tex_pos & (texHeight - 1);
//			tex_pos += step;

//			int color = cub->data->textures[tex_num][texHeight * tex_y + tex_x];
//			if (side == 1)
//				color = (color >> 1) & 8355711;  // 어둡게
//			cub->ray.buf[y][x] = color;
//		}

//		// 바닥
//		for(int y = draw_end; y < SCREEN_HEIGHT; y++)
//			cub->ray.buf[y][x] = cub->data->floor_clr;
//			//   cub->ray.buf[y][x] = 0x888888;
//	}
//}


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
