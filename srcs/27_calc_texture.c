/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   27_calc_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:40:53 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/22 20:31:20 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_calc_texture(t_cub *cub)
{
	double	wall_x;

	if (cub->ray.side == 0)
		wall_x = cub->ray.pos_y + cub->ray.perp_wall_dist * cub->ray.raydir_y;
	else
		wall_x = cub->ray.pos_x + cub->ray.perp_wall_dist * cub->ray.raydir_x;
	wall_x -= floor(wall_x);
	cub->ray.tex_x = (int)(wall_x * (double)TEXWIDTH);
	if (cub->ray.side == 0 && cub->ray.raydir_x > 0)
		cub->ray.tex_x = TEXWIDTH - cub->ray.tex_x - 1;
	if (cub->ray.side == 1 && cub->ray.raydir_y < 0)
		cub->ray.tex_x = TEXWIDTH - cub->ray.tex_x - 1;
}
