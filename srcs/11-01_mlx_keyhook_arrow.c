/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11-01_mlx_keyhook_arrow.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:30:12 by kjung             #+#    #+#             */
/*   Updated: 2025/02/22 23:33:36 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_key_l_arrow(t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->ray.dir_x;
	cub->ray.dir_x = cub->ray.dir_x * cos(cub->ray.rot_speed) - \
					cub->ray.dir_y * sin(cub->ray.rot_speed);
	cub->ray.dir_y = old_dir_x * sin(cub->ray.rot_speed) + \
					cub->ray.dir_y * cos(cub->ray.rot_speed);
	old_plane_x = cub->ray.plane_x;
	cub->ray.plane_x = cub->ray.plane_x * cos(cub->ray.rot_speed) - \
						cub->ray.plane_y * sin(cub->ray.rot_speed);
	cub->ray.plane_y = old_plane_x * sin(cub->ray.rot_speed) + \
						cub->ray.plane_y * cos(cub->ray.rot_speed);
}

void	ft_key_r_arrow(t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->ray.dir_x;
	cub->ray.dir_x = cub->ray.dir_x * cos(-cub->ray.rot_speed) - \
					cub->ray.dir_y * sin(-cub->ray.rot_speed);
	cub->ray.dir_y = old_dir_x * sin(-cub->ray.rot_speed) + \
					cub->ray.dir_y * cos(-cub->ray.rot_speed);
	old_plane_x = cub->ray.plane_x;
	cub->ray.plane_x = cub->ray.plane_x * cos(-cub->ray.rot_speed) - \
						cub->ray.plane_y * sin(-cub->ray.rot_speed);
	cub->ray.plane_y = old_plane_x * sin(-cub->ray.rot_speed) + \
						cub->ray.plane_y * cos(-cub->ray.rot_speed);
}
