/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_validate_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:32:22 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/06 16:32:24 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	padding_map(t_file **f)
{
	int		i;
	int		margin;
	char	*padded;

	i = 0;
	while (i < (*f)->map_height)
	{
		if ((int) ft_strlen((*f)->maparr[i]) < (*f)->map_width)
		{
			margin = (*f)->map_width - ft_strlen((*f)->maparr[i]);
			padded = malloc(sizeof(char *) * ((*f)->map_width + 1));
			ft_memcpy(padded, (*f)->maparr[i], ft_strlen((*f)->maparr[i]));
			ft_memset(padded + ft_strlen((*f)->maparr[i]), ' ', margin);
			padded[(*f)->map_width] = '\0';
			free((*f)->maparr[i]);
			(*f)->maparr[i] = padded;
		}
		i++;
	}
	return (0);
}

int	check_inside(int i, int *flag, t_file **f)
{
	int	j;

	j = 1;
	if ((*f)->maparr[i][0] != '1' || \
		!((*f)->maparr[i][(*f)->map_width - 1] == '1' || \
		(*f)->maparr[i][(*f)->map_width - 1] == ' '))
		return (1);
	while ((*f)->maparr[i][j])
	{
		if (check_inside_zero((*f)->maparr, i, j))
			return (1);
		if ((*f)->maparr[i][j] == 'N' || (*f)->maparr[i][j] == 'S' || \
			(*f)->maparr[i][j] == 'E' || (*f)->maparr[i][j] == 'W')
		{
			if (*flag == 1)
				return (1);
			*flag = 1;
			get_pos((*f)->maparr, i, j, f);
		}
		j++;
	}
	return (0);
}

int	map_check(char **map, int width, int height, t_file **f)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < height)
	{
		if (i == 0 || i == height - 1)
		{
			if (check_frontier(map, i, width))
				return (1);
		}
		else
		{
			if (check_inside(i, &flag, f))
				return (1);
		}
		i++;
	}
	if (!flag)
		return (1);
	return (0);
}

int	ft_validate_map(t_file **f)
{
	padding_map(f);
	if (map_check((*f)->maparr, (*f)->map_width, (*f)->map_height, f))
		ft_exit("Invalid Map\n", 1, f);
	else
		printf("Success");
	return (0);
}
