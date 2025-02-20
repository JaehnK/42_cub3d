/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:38:34 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/20 16:36:49 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	cub->data = malloc(sizeof(t_data));
	cub->file = NULL;
	ft_mlx_init(cub->data);
	ft_parse_file(argc, argv, &(cub->file));
	if (init_world_map(cub))
	{
		printf("Error: World map initialization failed\n");
		return (-1);
	}
	if (init_ray_info(cub))
	{
		printf("Error: Ray info initialization failed\n");
		return (-1);
	}
	ft_read_cub_value(&(cub->file), &cub);
	mlx_loop_hook(cub->data->mlx, (void *)main_loop, &cub);
	mlx_hook(cub->data->win, X_EVENT_KEY_PRESS, KEY_PRESS_MASK, key_press, cub);
	mlx_hook(cub->data->win, X_EVENT_KEY_EXIT, 0, close_window, cub);
	mlx_loop(cub->data->mlx);
	return (0);
}
