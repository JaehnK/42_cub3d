/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   25_hit_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:12:47 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/20 17:12:49 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_get_side(int *nxt_map_x, int *nxt_map_y, t_cub *cub)
{
	if (cub->ray.side_dist_x < cub->ray.side_dist_y)
	{
		cub->ray.side_dist_x += cub->ray.delta_dist_x;
		*nxt_map_x = cub->ray.map_x + cub->ray.step_x;
		cub->ray.side = 0;
	}
	else
	{
		cub->ray.side_dist_y += cub->ray.delta_dist_y;
		*nxt_map_y = cub->ray.map_y + cub->ray.step_y;
		cub->ray.side = 1;
	}
}

void	ft_hit_checker(t_cub *cub)
{
	int	nxt_map_x;
	int	nxt_map_y;

	cub->ray.hit = 0;
	while (cub->ray.hit == 0)
	{
		nxt_map_x = cub->ray.map_x;
		nxt_map_y = cub->ray.map_y;
		ft_get_side(&nxt_map_x, &nxt_map_y, cub);
		if (nxt_map_x < 0 || nxt_map_x >= cub->ray.map_width || \
			nxt_map_y < 0 || nxt_map_y >= cub->ray.map_height)
		{
			cub->ray.hit = 1;
			break ;
		}
		cub->ray.map_x = nxt_map_x;
		cub->ray.map_y = nxt_map_y;
		if (cub->ray.world_map[cub->ray.map_y][cub->ray.map_x] > 0)
			cub->ray.hit = 1;
	}
}
