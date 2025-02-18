/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_read_cub_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:26:15 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/18 09:26:16 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_image(t_cub **cub, int *texture, char *path, t_img *img)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	// ft_memset(&img, 0, sizeof(t_img));
	printf("path: %s\n", path);
	img->img = mlx_xpm_file_to_image((*cub)->data->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->size_l, &img->endian);
	printf("%d %d\n", img->img_height, img->img_width);
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image((*cub)->data->mlx, img->img);
}

void	ft_read_cub_value(t_file **f, t_cub **cub)
{
	int i;
	t_img	img;

	i = 0;
	(*cub)->data->textures = malloc(sizeof(int *) * 5);
	while (i < 4)
	{
		(*cub)->data->textures[i] = (int *)ft_calloc(sizeof(int), (TEX_H * TEX_W));
		if (!(*cub)->data->textures[i])
			exit(1);
		i++;
	}
	(*cub)->data->textures[i] = NULL;
	load_image(cub, (*cub)->data->textures[0], (*f)->ea_dir, &img);
	load_image(cub, (*cub)->data->textures[1], (*f)->we_dir, &img);
	load_image(cub, (*cub)->data->textures[2], (*f)->so_dir, &img);
	load_image(cub, (*cub)->data->textures[3], (*f)->no_dir, &img);
}
