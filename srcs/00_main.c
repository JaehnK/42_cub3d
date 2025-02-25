/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:38:34 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/22 20:39:29 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_initalise(int ac, char **av, t_cub *cub)
{
	cub->data = ft_calloc(sizeof(t_data), 1);
	cub->file = NULL;
	if (ft_parse_file(ac, av, &(cub->file)))
	{
		ft_free_cub(cub);
		return (1);
	}
	if (init_world_map(cub))
	{
		ft_putstr_fd("Error\nWorld map initialization failed\n", 2);
		return (1);
	}
	if (init_ray_info(cub))
	{
		ft_putstr_fd("Error\nRay info initialization failed\n", 2);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = ft_calloc(sizeof(t_cub), 1);
	if (ft_initalise(argc, argv, cub))
	{
		return (1);
	}
	ft_mlx_init(cub->data);
	if (ft_read_cub_value(&(cub->file), &cub))
	{
		close_window((void *) cub);
		return (1);
	}	
	mlx_loop_hook(cub->data->mlx, (void *)main_loop, &cub);
	mlx_hook(cub->data->win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->data->win, 17, 0, close_window, cub);
	mlx_loop(cub->data->mlx);
	return (0);
}
