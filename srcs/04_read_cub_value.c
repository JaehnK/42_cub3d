/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_read_cub_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:26:15 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/22 20:30:52 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_image(t_cub **cub, int *texture, char *path, t_img *img)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	img->img = mlx_xpm_file_to_image(\
			(*cub)->data->mlx, path, &img->img_width, &img->img_height);
	if (img->img == NULL)
		return (1);
	img->data = (int *)mlx_get_data_addr(\
			img->img, &img->bits_per_pixel, &img->size_l, &img->endian);
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
	return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static int	load_colour(char *str)
{
	int		i;
	int		rgb[3];
	int		colour;
	char	**colours;

	i = 0;
	colours = ft_split(str, ',');
	if (!colours[1])
		return (-1);
	while (i < 3)
	{
		rgb[i] = ft_atoi(colours[i]);
		free(colours[i++]);
	}
	colour = create_trgb(0, rgb[0], rgb[1], rgb[2]);
	free(colours);
	return (colour);
}

int	ft_read_cub_value(t_file **f, t_cub **cub)
{
	int		i;
	int		flag;
	t_img	img;

	i = 0;
	flag = 0;
	(*cub)->data->textures = malloc(sizeof(int *) * 5);
	while (i < 4)
	{
		(*cub)->data->textures[i] = \
			(int *)ft_calloc(sizeof(int), (TEXHEIGHT * TEXWIDTH));
		if (!(*cub)->data->textures[i])
			exit(1);
		i++;
	}
	(*cub)->data->textures[i] = NULL;
	flag = load_image(cub, (*cub)->data->textures[0], (*f)->ea_dir, &img);
	flag = load_image(cub, (*cub)->data->textures[1], (*f)->we_dir, &img);
	flag = load_image(cub, (*cub)->data->textures[2], (*f)->so_dir, &img);
	flag = load_image(cub, (*cub)->data->textures[3], (*f)->no_dir, &img);
	(*cub)->data->ceiling_clr = load_colour((*cub)->file->c_dir);
	(*cub)->data->floor_clr = load_colour((*cub)->file->f_dir);
	if (flag || (*cub)->data->ceiling_clr < 0 || (*cub)->data->floor_clr < 0)
		return (1);
	return (0);
}
