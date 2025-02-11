/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:58:56 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/04 09:58:59 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub *cub;

	cub = malloc(sizeof(t_cub));
	cub->data = malloc(sizeof(t_data));
	cub->file = NULL;
	ft_mlx_init(cub->data);
	ft_parse_file(argc, argv, &(cub->file));
	cub->file->plane_x = 0;
	cub->file->plane_y = 0.66;
	mlx_loop_hook(cub->data->mlx, main_loop, &cub);
    mlx_loop(cub->data->mlx);
}
