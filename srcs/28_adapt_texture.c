/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   28_adapt_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:59:10 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/22 20:32:10 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_choose_texture(t_cub *cub)
{
	if (cub->ray.side == 0)
	{
		if (cub->ray.raydir_x > 0)
			cub->ray.tex_num = 0;
		else
			cub->ray.tex_num = 1;
	}
	else
	{
		if (cub->ray.raydir_y > 0)
			cub->ray.tex_num = 2;
		else
			cub->ray.tex_num = 3;
	}
}

static void	adapt_ceiling_texture(int x, t_cub *cub)
{
	int	y;

	y = 0;
	while (y < cub->ray.draw_start)
	{
		//printf("%d %d\n",y,cub->ray.draw_start);
		cub->ray.buf[y][x] = cub->data->ceiling_clr;
		y++;
	}
}

static void	adapt_wall_texture(int x, t_cub *cub)
{
	int		y;
	int		tex_y;
	int		colour;
	double	step;
	double	tex_pos;

	y = cub->ray.draw_start;
	step = 1.0 * TEXHEIGHT / cub->ray.line_height;
	tex_pos = (cub->ray.draw_start - SCREEN_HEIGHT / 2 + \
				cub->ray.line_height / 2) * step;
	while (y < cub->ray.draw_end)
	{
		tex_y = (int)tex_pos & (TEXHEIGHT - 1);
		tex_pos += step;
		colour = cub->data->textures[cub->ray.tex_num] \
				[TEXHEIGHT * tex_y + cub->ray.tex_x];
		if (cub->ray.side == 1)
			colour = (colour >> 1) & 8355711;
		cub->ray.buf[y][x] = colour;
		y++;
	}
}

static void	adapt_floor_texture(int x, t_cub *cub)
{
	int	y;

	y = cub->ray.draw_end;
	while (y < SCREEN_HEIGHT)
	{
		//printf("%d\n",y);
		cub->ray.buf[y][x] = cub->data->floor_clr;
		y++;
	}
}

void	ft_adapt_texture(int x, t_cub *cub)
{
	ft_choose_texture(cub);
	adapt_ceiling_texture(x, cub);
	adapt_wall_texture(x, cub);
	adapt_floor_texture(x, cub);
}
