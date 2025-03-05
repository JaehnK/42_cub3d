/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02-01_parse_map_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:15:59 by kjung             #+#    #+#             */
/*   Updated: 2025/02/26 18:33:30 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		else
			return (1);
	}
	return (0);
}

void	char_check(char c)
{
	if (c != '1' && c != '0' && c != 'N' \
	&& c != 'E' && c != 'W' && c != 'S' \
	&& c != '\n' && c != ' ' && c != '\t')
	{
		ft_putstr_fd("Error\nInvalid Map Character\n", 2);
		exit(1);
	}
}
