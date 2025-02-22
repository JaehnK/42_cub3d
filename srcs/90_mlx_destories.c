/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   90_mlx_destories.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:11:50 by kjung             #+#    #+#             */
/*   Updated: 2025/02/22 19:10:15 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_int_2d_arr_free(int **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i++]);
	}
	free(arr);
}

void	ft_free_cub(t_cub *cb)
{
	free_file_struct(&(cb->file));
	ft_int_2d_arr_free(cb->ray.world_map);
	ft_int_2d_arr_free(cb->data->textures);
	free(cb->data);
	free(cb->file);
	free(cb);
}

int	close_window(void *param)
{
	t_cub	*p;

	p = (t_cub *)param;
	if (!p)
		return (1);
	if (p->data)
	{
		if (p->data->win && p->data->mlx)
			mlx_destroy_window(p->data->mlx, p->data->win);
		if (p->data->img.img && p->data->mlx)
			mlx_destroy_image(p->data->mlx, p->data->img.img);
		if (p->data->mlx)
			mlx_destroy_display(p->data->mlx);
		free(p->data->mlx);
	}
	ft_free_cub(p);
	exit(0);
	return (0);
}
