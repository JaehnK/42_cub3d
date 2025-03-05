/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_mlx_keyhook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:42:53 by kjung             #+#    #+#             */
/*   Updated: 2025/02/23 01:03:19 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_key_w(t_cub *cub)
{
	int	new_x;
	int	new_y;

	new_x = (int)(cub->ray.pos_x + cub->ray.dir_x * cub->ray.move_speed);
	new_y = (int)(cub->ray.pos_y + cub->ray.dir_y * cub->ray.move_speed);
	if (new_x >= 0 && new_x < cub->ray.map_width && \
			(int) cub->ray.pos_y >= 0 && \
			(int) cub->ray.pos_y < cub->ray.map_height && \
			!cub->ray.world_map[(int) cub->ray.pos_y][new_x])
		cub->ray.pos_x += cub->ray.dir_x * cub->ray.move_speed;
	if ((int) cub->ray.pos_x >= 0 && \
			(int )cub->ray.pos_x < cub->ray.map_width && \
			new_y >= 0 && new_y < cub->ray.map_height && \
			!cub->ray.world_map[new_y][(int) cub->ray.pos_x])
		cub->ray.pos_y += cub->ray.dir_y * cub->ray.move_speed;
}

void	ft_key_s(t_cub *cub)
{
	int	new_x;
	int	new_y;

	new_x = (int)(cub->ray.pos_x - cub->ray.dir_x * cub->ray.move_speed);
	new_y = (int)(cub->ray.pos_y - cub->ray.dir_y * cub->ray.move_speed);
	if (new_x >= 0 && new_x < cub->ray.map_width && \
			(int)cub->ray.pos_y >= 0 && \
			(int)cub->ray.pos_y < cub->ray.map_height && \
			!cub->ray.world_map[(int)cub->ray.pos_y][new_x])
		cub->ray.pos_x -= cub->ray.dir_x * cub->ray.move_speed;
	if ((int) cub->ray.pos_x >= 0 && \
			(int)cub->ray.pos_x < cub->ray.map_width && \
			new_y >= 0 && new_y < cub->ray.map_height && \
			!cub->ray.world_map[new_y][(int)cub->ray.pos_x])
		cub->ray.pos_y -= cub->ray.dir_y * cub->ray.move_speed;
}

void	ft_key_a(t_cub *cub)
{
	int	new_x;
	int	new_y;

	new_x = (int)(cub->ray.pos_x + (-cub->ray.dir_y) * cub->ray.move_speed);
	new_y = (int)(cub->ray.pos_y + cub->ray.dir_x * cub->ray.move_speed);
	if (new_x >= 0 && new_x < cub->ray.map_width && \
			(int)cub->ray.pos_y >= 0 && \
			(int)cub->ray.pos_y < cub->ray.map_height && \
			!cub->ray.world_map[(int)cub->ray.pos_y][new_x])
		cub->ray.pos_x += (-cub->ray.dir_y) * cub->ray.move_speed;
	if ((int)cub->ray.pos_x >= 0 && \
			(int)cub->ray.pos_x < cub->ray.map_width && \
			new_y >= 0 && new_y < cub->ray.map_height && \
			!cub->ray.world_map[new_y][(int)cub->ray.pos_x])
		cub->ray.pos_y += cub->ray.dir_x * cub->ray.move_speed;
}

void	ft_key_d(t_cub *cub)
{
	int	new_x;
	int	new_y;

	new_x = (int)(cub->ray.pos_x + cub->ray.dir_y * cub->ray.move_speed);
	new_y = (int)(cub->ray.pos_y + (-cub->ray.dir_x) * cub->ray.move_speed);
	if (new_x >= 0 && new_x < cub->ray.map_width && \
			(int)cub->ray.pos_y >= 0 && \
			(int)cub->ray.pos_y < cub->ray.map_height && \
			!cub->ray.world_map[(int)cub->ray.pos_y][new_x])
		cub->ray.pos_x += cub->ray.dir_y * cub->ray.move_speed;
	if ((int)cub->ray.pos_x >= 0 && \
			(int)cub->ray.pos_x < cub->ray.map_width && \
			new_y >= 0 && new_y < cub->ray.map_height && \
			!cub->ray.world_map[new_y][(int)cub->ray.pos_x])
		cub->ray.pos_y += (-cub->ray.dir_x) * cub->ray.move_speed;
}

int	key_press(int key, t_cub *cub)
{
	if (key == 119)
		ft_key_w(cub);
	if (key == 115)
		ft_key_s(cub);
	if (key == 97)
		ft_key_a(cub);
	if (key == 100)
		ft_key_d(cub);
	if (key == 65307)
		close_window((void *) cub);
	if (key == 65361)
		ft_key_l_arrow(cub);
	if (key == 65363)
		ft_key_r_arrow(cub);
	return (0);
}
