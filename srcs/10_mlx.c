/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:49:59 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/11 14:30:59 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, SCREEN_W, SCREEN_H, "CUB 3D");
	data->img.img = mlx_new_image(data->mlx, SCREEN_W, SCREEN_H);
	data->img.data = (int *) mlx_get_data_addr(data->img.img, \
									&(data->img.bits_per_pixel), \
									&(data->img.line_length), \
									&(data->img.endian));
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.line_length + x * \
			(data->img.bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}
