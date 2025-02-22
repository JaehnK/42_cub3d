/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22_init_ray_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:11:22 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/19 14:11:23 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	initalise_ray_dir(t_cub *cub)
{
	if (cub->file->pos_dir >= '3')
	{
		cub->ray.dir_y = 1.0;
		cub->ray.plane_x = 0.66;
		if (cub->file->pos_dir == '3')
			cub->ray.plane_x *= -1.0;
		else if (cub->file->pos_dir == '4')
			cub->ray.dir_x *= -1.0;
	}
	else if (cub->file->pos_dir >= '1')
	{
		cub->ray.dir_x = 1.0;
		cub->ray.plane_y = 0.66;
		if (cub->file->pos_dir == '2')
		{
			cub->ray.dir_x *= -1.0;
			cub->ray.plane_y *= -1.0;
		}
	}
	else
		return (1);
	return (0);
}

int	init_ray_info(t_cub *cub)
{
	if (cub->file->pos_x < 0 || cub->file->pos_x >= cub->ray.map_width || \
		cub->file->pos_y < 0 || cub->file->pos_y >= cub->ray.map_height)
	{
		printf("Error: Invalid player position (%f, %f) for map size %dx%d\n",
			cub->file->pos_x, cub->file->pos_y,
			cub->ray.map_width, cub->ray.map_height);
		return (1);
	}
	cub->ray.pos_x = cub->file->pos_x + 0.5;
	cub->ray.pos_y = cub->file->pos_y + 0.5;
	ft_memset(cub->ray.buf, 0, sizeof(cub->ray.buf));
	cub->ray.dir_x = 0.0;
	cub->ray.dir_y = 0.0;
	cub->ray.plane_x = 0.0;
	cub->ray.plane_y = 0.0;
	if (initalise_ray_dir(cub))
		return (1);
	cub->ray.move_speed = MOVE_SPEED;
	cub->ray.rot_speed = ROT_SPEED;
	return (0);
}
