/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_init_worldmap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:30:31 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/22 19:11:18 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	fail_alloc_worldmap(int i, t_ray_info *ray)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(ray->world_map[j]);
		j++;
	}
	free(ray->world_map);
	return (1);
}

static void	insert_value_at_worldmap(int i, int width, \
									t_ray_info *ray, t_file *file)
{
	int	j;

	j = 0;
	while (j < width)
	{
		if (file->maparr[i][j] == '1')
			ray->world_map[i][j] = 1;
		else if (file->maparr[i][j] == ' ')
			ray->world_map[i][j] = 1;
		else
			ray->world_map[i][j] = 0;
		j++;
	}
}

int	init_world_map(t_cub *cub)
{
	int	i;

	i = 0;
	cub->ray.map_height = cub->file->map_height;
	cub->ray.map_width = cub->file->map_width;
	cub->ray.world_map = (int **)malloc(sizeof(int *) * \
						(cub->ray.map_height + 1));
	if (!cub->ray.world_map)
		return (1);
	while (i < cub->ray.map_height)
	{
		cub->ray.world_map[i] = (int *)malloc(sizeof(int) * cub->ray.map_width);
		if (!cub->ray.world_map[i])
			return (fail_alloc_worldmap(i, &(cub->ray)));
		insert_value_at_worldmap(i, cub->ray.map_width, \
								&(cub->ray), cub->file);
		i++;
	}
	cub->ray.world_map[i] = NULL;
	return (0);
}
