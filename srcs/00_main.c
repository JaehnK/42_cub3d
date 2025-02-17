/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:58:56 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/11 16:26:10 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_file(char **f)
{
	for (int i = 0; f[i]; i++)
	{
		printf("%s:%d\n", f[i], i);
	}

}

int	main(int argc, char **argv)
{
	t_cub *cub;

	cub = malloc(sizeof(t_cub));
	cub->data = malloc(sizeof(t_data));
	cub->file = NULL;
	ft_mlx_init(cub->data);
	ft_parse_file(argc, argv, &(cub->file));
	print_file(cub->file->maparr);
	cub->data->buf = 0;
	cub->file->plane_x = 0;
	cub->file->plane_y = 0.66;
	mlx_loop_hook(cub->data->mlx, main_loop, &cub);
    mlx_loop(cub->data->mlx);
}
