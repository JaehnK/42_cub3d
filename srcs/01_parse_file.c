/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:10:09 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/22 18:55:58 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_file(int ac, char **av, t_file **f)
{
	char	*tmp;

	if (ac != 2)
	{
		ft_putstr_fd("Error:\nInvalid Arguments\n", 2);
		return (1);
	}
	tmp = ft_substr(av[1], ft_strlen(av[1]) - 4, 4);
	if (ft_strncmp(tmp, ".cub", 4) != 0)
	{
		free(tmp);
		ft_putstr_fd("Error:\nCheck Filename\n", 2);
		return (1);
	}
	free(tmp);
	(*f)->filename = ft_strdup(av[1]);
	return (0);
}

char	*clean_newline(char *line)
{
	char	**tmp;
	char	*ret;

	tmp = ft_split(line, '\n');
	ret = ft_strdup(tmp[0]);
	ft_split_free(tmp);
	return (ret);
}

int	assign_dir(char *line, t_file **f)
{
	int		flag;
	char	**contents;

	flag = 0;
	contents = ft_split(line, ' ');
	if (!ft_strncmp(contents[0], "NO", 2))
		(*f)->no_dir = clean_newline(contents[1]);
	else if (!ft_strncmp(contents[0], "SO", 2))
		(*f)->so_dir = clean_newline(contents[1]);
	else if (!ft_strncmp(contents[0], "WE", 2))
		(*f)->we_dir = clean_newline(contents[1]);
	else if (!ft_strncmp(contents[0], "EA", 2))
		(*f)->ea_dir = clean_newline(contents[1]);
	else if (!ft_strncmp(contents[0], "F", 1))
		(*f)->f_dir = clean_newline(contents[1]);
	else if (!ft_strncmp(contents[0], "C", 1))
		(*f)->c_dir = clean_newline(contents[1]);
	else
		flag = 1;
	ft_split_free(contents);
	if (flag)
		return (1);
	return (0);
}

int	get_dirs(int fd, t_file **f)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_check_empty_line(line))
		{
			free(line);
			continue ;
		}
		if (assign_dir(line, f))
			return (1);
		free(line);
		if (ft_has_dirs(*f))
			break ;
	}
	if (!line)
		ft_exit("Error\nFailed To Parse File", 18, f);
	return (0);
}

int	ft_parse_file(int ac, char **av, t_file **f)
{
	int		fd;

	*f = ft_calloc(sizeof(t_file), 1);
	if (validate_file(ac, av, f))
		return (1);
	fd = open((*f)->filename, O_RDONLY);
	if (get_dirs(fd, f))
	{
		close(fd);
		return (1);
	}
	if (ft_parse_map(fd, f))
		return (1);
	close(fd);
	return (0);
}
