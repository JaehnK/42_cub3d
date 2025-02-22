/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03-01_validate_map_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:30:16 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/21 15:19:53 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_frontier(char **map, int i, int width)
{
	int	j;

	j = 0;
	while (map[i][j] && !(map[i][j] != '1' && map[i][j] != ' '))
		j++;
	if (j < width - 1)
		return (1);
	return (0);
}

int	check_inside_zero(char **map, int i, int j)
{
	if (map[i][j] == '0')
	{
		if (map[i - 1][j] == ' ' || map[i - 1][j - 1] == ' ' || \
			map[i + 1][j] == ' ' || map[i + 1][j + 1] == ' ')
			return (1);
	}
	return (0);
}

static int	get_pos_sub(char **map, int i, int j, t_file **f)
{
	if (map[i][j] == 'S')
	{
		(*f)->pos_dir = '3';
		(*f)->pos_dir_x = 0.0;
		(*f)->pos_dir_y = -1.0;
		map[i][j] = '0';
		return (1);
	}
	else if (map[i][j] == 'N')
	{
		(*f)->pos_dir = '4';
		(*f)->pos_dir_x = 0.0;
		(*f)->pos_dir_y = 1.0;
		map[i][j] = '0';
		return (1);
	}
	return (0);
}

int	get_pos(char **map, int i, int j, t_file **f)
{
	(*f)->pos_x = j;
	(*f)->pos_y = i;
	if (map[i][j] == 'E')
	{
		(*f)->pos_dir = '1';
		(*f)->pos_dir_x = 1.0;
		(*f)->pos_dir_y = 0.0;
		(*f)->plane_x = 0.0;
		(*f)->plane_y = 0.66;
		map[i][j] = '0';
	}
	else if (map[i][j] == 'W')
	{
		(*f)->pos_dir = '2';
		(*f)->pos_dir_x = -1.0;
		(*f)->pos_dir_y = 0.0;
		map[i][j] = '0';
	}
	else
	{
		if (!get_pos_sub(map, i, j, f))
			return (0);
	}
	return (0);
}
