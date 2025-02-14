/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_fileparse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:10:09 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/04 10:10:11 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	validate_file(int ac, char **av, t_file **f)
{
	char	*tmp;

	if (ac != 2)
	{
		ft_putstr_fd("Error:\nInvalid Arguments\n", 2);
		free(*f);
		exit(1);
	}
	tmp = ft_substr(av[1], ft_strlen(av[1]) - 4, 4);
	if (ft_strncmp(tmp, ".cub", 4) != 0)
	{
		free(*f);
		free(tmp);
		ft_putstr_fd("Error:\nCheck Filename\n", 2);
		exit(1);
	}
	free(tmp);
	(*f)->filename = ft_strdup(av[1]);
	return (0);
}

int	assign_dir(char *line, t_file **f)
{
	int		flag;
	char	**contents;

	flag = 0;
	contents = ft_split(line, ' ');
	if (!ft_strncmp(contents[0], "NO", 2))
		(*f)->no_dir = ft_strdup(contents[1]);
	else if (!ft_strncmp(contents[0], "SO", 2))
		(*f)->so_dir = ft_strdup(contents[1]);
	else if (!ft_strncmp(contents[0], "WE", 2))
		(*f)->we_dir = ft_strdup(contents[1]);
	else if (!ft_strncmp(contents[0], "EA", 2))
		(*f)->ea_dir = ft_strdup(contents[1]);
	else if (!ft_strncmp(contents[0], "F", 1))
		(*f)->f_dir = ft_strdup(contents[1]);
	else if (!ft_strncmp(contents[0], "C", 1))
		(*f)->c_dir = ft_strdup(contents[1]);
	else
		flag = 1;
	ft_split_free(contents);
	if (flag)
		ft_exit("Error\nInvalid Direction\n", 1, f);
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
		assign_dir(line, f);
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
	validate_file(ac, av, f);
	fd = open((*f)->filename, O_RDONLY);
	get_dirs(fd, f);
	ft_parse_map(fd, f);
	close(fd);
	return (0);
}
