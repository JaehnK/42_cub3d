/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04-01_validate_map_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:30:16 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/09 19:30:17 by jaehukim         ###   ########.fr       */
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

int	get_pos(char **map, int i, int j, t_file **f)
{
	(*f)->pos_x = j;
	(*f)->pos_y = i;
	if (map[i][j] == 'E')
		(*f)->pos_dir = 1;
	else if (map[i][j] == 'W')
		(*f)->pos_dir = 2;
	else if (map[i][j] == 'S')
		(*f)->pos_dir = 3;
	else if (map[i][j] == 'N')
		(*f)->pos_dir = 4;
	else
		return (-1);
	return (0);
}
