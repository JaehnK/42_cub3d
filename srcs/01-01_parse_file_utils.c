/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_parse_file_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:01:43 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/04 11:01:44 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_empty_line(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (1);
	while (i < ft_strlen(str))
	{
		if (ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_has_dirs(t_file *f)
{
	if (f->no_dir && f->so_dir && f->we_dir && \
		f->ea_dir && f->f_dir && f->c_dir)
		return (1);
	return (0);
}
