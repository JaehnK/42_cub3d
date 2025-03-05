/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:32:14 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/26 18:36:39 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map_list	*alloc_new_node(int idx, char *line, t_map_list **head)
{
	t_map_list	*new;
	t_map_list	*tmp;

	new = malloc(sizeof(t_map_list));
	if (!new)
		perror("allocation failed\n");
	new->idx = idx;
	new->line = line;
	new->next = NULL;
	if (!head)
		return (new);
	tmp = *head;
	while (tmp && tmp->next)
		tmp = (tmp)->next;
	(tmp)->next = new;
	return (new);
}

t_map_list	*alloc_map_list(int fd)
{
	int			i;
	int			idx;
	char		*line;
	t_map_list	*head;

	idx = 0;
	line = get_next_line(fd);
	head = NULL;
	while (line)
	{
		i = 0;
		while (line[i])
		{
			char_check(line[i]);
			i++;
		}
		if (!head)
			head = alloc_new_node(idx++, line, NULL);
		else
			alloc_new_node(idx++, line, &head);
		line = get_next_line(fd);
		head->idx = idx;
	}
	return (head);
}

static int	process_map_node(t_map_list **node, t_file **f, \
					int *i, int *mapwidth)
{
	t_map_list	*tmp;
	char		**line;

	if (!ft_isspace2((*node)->line))
	{
		tmp = (*node);
		if ((*node) != NULL)
			(*node) = (*node)->next;
		free(tmp->line);
		free(tmp);
		return (1);
	}
	line = ft_split((*node)->line, '\n');
	(*f)->maparr[(*i)] = ft_spacejump(line[0]);
	if ((int)ft_strlen((*f)->maparr[(*i)]) > (*mapwidth))
		(*mapwidth) = ft_strlen((*f)->maparr[(*i)]);
	(*i)++;
	ft_split_free(line);
	tmp = (*node);
	(*node) = (*node)->next;
	free(tmp->line);
	free(tmp);
	return (0);
}

int	convert_list_to_array(t_map_list **node, t_file **f)
{
	int			i;
	int			mapwidth;

	i = 0;
	mapwidth = 0;
	(*f)->maparr = malloc(sizeof(char *) * ((*node)->idx + 1));
	if (!(*f)->maparr)
		return (1);
	while (*node)
	{
		if (process_map_node(node, f, &i, &mapwidth))
			continue ;
	}
	(*f)->maparr[i] = NULL;
	(*f)->map_width = mapwidth;
	(*f)->map_height = i;
	return (0);
}

int	ft_parse_map(int fd, t_file **f)
{
	t_map_list	*node;

	node = alloc_map_list(fd);
	if (!node)
		return (1);
	convert_list_to_array(&node, f);
	if (ft_validate_map(f))
		return (1);
	return (0);
}
