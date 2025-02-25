/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22_init_ray_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:11:22 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/23 00:19:55 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_ray_info(t_cub *cub)
{
	if (cub->file->pos_x < 0 || cub->file->pos_x >= cub->ray.map_width || \
		cub->file->pos_y < 0 || cub->file->pos_y >= cub->ray.map_height)
	{
		printf("Error\nInvalid player position (%f, %f) for map size %dx%d\n",
			cub->file->pos_x, cub->file->pos_y,
			cub->ray.map_width, cub->ray.map_height);
		return (1);
	}
	cub->ray.pos_x = cub->file->pos_x + 0.5;
	cub->ray.pos_y = cub->file->pos_y + 0.5;
	ft_memset(cub->ray.buf, 0, sizeof(cub->ray.buf));
	cub->ray.dir_x = cub->file->pos_dir_x;
	cub->ray.dir_y = cub->file->pos_dir_y;
	cub->ray.plane_x = cub->file->plane_x;
	cub->ray.plane_y = cub->file->plane_y;
	cub->ray.move_speed = MOVE_SPEED;
	cub->ray.rot_speed = ROT_SPEED;
	return (0);
}
