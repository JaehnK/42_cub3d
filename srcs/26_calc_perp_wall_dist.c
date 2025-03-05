/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   26_calc_perp_wall_dist.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:30:27 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/26 18:22:06 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_calc_perp_wall_dist(t_cub *cub)
{
	if (cub->ray.side == 0)
		cub->ray.perp_wall_dist = (cub->ray.map_x - cub->ray.pos_x + \
								(1 - cub->ray.step_x) / 2) / cub->ray.raydir_x;
	else
		cub->ray.perp_wall_dist = (cub->ray.map_y - cub->ray.pos_y + \
								(1 - cub->ray.step_y) / 2) / cub->ray.raydir_y;
	cub->ray.line_height = (int)(SCREEN_HEIGHT / cub->ray.perp_wall_dist);
	cub->ray.draw_start = -cub->ray.line_height / 2 + SCREEN_HEIGHT / 2;
	if (cub->ray.draw_start < 0)
		cub->ray.draw_start = 0;
	cub->ray.draw_end = cub->ray.line_height / 2 + SCREEN_HEIGHT / 2;
	if (cub->ray.draw_end >= SCREEN_HEIGHT)
		cub->ray.draw_end = SCREEN_HEIGHT;
}
