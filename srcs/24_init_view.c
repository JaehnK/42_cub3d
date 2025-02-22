/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_init_view.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:47:36 by kjung             #+#    #+#             */
/*   Updated: 2025/02/20 16:58:40 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_get_side_dist(t_cub *cub)
{
	if (cub->ray.raydir_x < 0)
		cub->ray.side_dist_x = (cub->ray.pos_x - cub->ray.map_x) \
								* cub->ray.delta_dist_x;
	else
		cub->ray.side_dist_x = (cub->ray.map_x + 1.0 - cub->ray.pos_x) \
								* cub->ray.delta_dist_x;
	if (cub->ray.raydir_y < 0)
		cub->ray.side_dist_y = (cub->ray.pos_y - cub->ray.map_y) \
								* cub->ray.delta_dist_y;
	else
		cub->ray.side_dist_y = (cub->ray.map_y + 1.0 - cub->ray.pos_y) \
								* cub->ray.delta_dist_y;
}

static void	ft_get_step(t_cub *cub)
{
	if (cub->ray.raydir_x < 0)
		cub->ray.step_x = -1;
	else
		cub->ray.step_x = 1;
	if (cub->ray.raydir_y < 0)
		cub->ray.step_y = -1;
	else
		cub->ray.step_y = 1;
}

static void	ft_get_delta_dist(t_cub *cub)
{
	if (cub->ray.raydir_x == 0)
		cub->ray.delta_dist_x = 1e30;
	else
		cub->ray.delta_dist_x = fabs(1 / cub->ray.raydir_x);
	if (cub->ray.raydir_y == 0)
		cub->ray.delta_dist_y = 1e30;
	else
		cub->ray.delta_dist_y = fabs(1 / cub->ray.raydir_y);
}

void	ft_init_player_view(int x, t_cub *cub)
{
	double	camera_x;

	camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	cub->ray.raydir_x = cub->ray.dir_x + cub->ray.plane_x * camera_x;
	cub->ray.raydir_y = cub->ray.dir_y + cub->ray.plane_y * camera_x;
	cub->ray.map_x = (int)cub->ray.pos_x;
	cub->ray.map_y = (int)cub->ray.pos_y;
	ft_get_delta_dist(cub);
	ft_get_step(cub);
	ft_get_side_dist(cub);
}
