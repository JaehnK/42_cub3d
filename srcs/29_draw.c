/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   29_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:35:49 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/20 18:35:53 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_HEIGHT)
	{
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(cub->data, j, i, cub->ray.buf[i][j]);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, \
							cub->data->img.img, 0, 0);
}
