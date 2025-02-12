/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:32:14 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/11 16:10:28 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	printlist(t_map_list *head)
{
	int	idx;

	idx = 0;
	while (head)
	{
		printf("%s: %d\n", head->line, idx++);
		head = head->next;
	}
}

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
	printf("node :%s", new->line);
	return (new);
}

t_map_list	*alloc_map_list(int fd)
{
	int			idx;
	char		*line;
	t_map_list	*head;

	idx = 0;
	line = get_next_line(fd);
	head = NULL;
	while (line)
	{
		if (line[0] != '1' && line[0] != '0')
			break ;
		else
		{
			if (!head)
				{
					head = alloc_new_node(idx++, line, NULL);				
				}
			else
				alloc_new_node(idx++, line, &head);
			line = get_next_line(fd);
		}
		head->idx = idx;
	}
	
	return (head);
}

int	convert_list_to_array(t_map_list **node, t_file **f)
{
	int			i;
	int			mapwidth;
	char		**line;
	t_map_list	*tmp;

	i = 0;
	mapwidth = 0;
	(*f)->maparr = malloc(sizeof(char *) * ((*node)->idx + 1));
	while (*node)
	{
		line = ft_split((*node)->line, '\n');
		(*f)->maparr[i++] = ft_strdup(line[0]);
		if ((int) ft_strlen((*f)->maparr[i - 1]) > mapwidth)
			mapwidth = ft_strlen((*f)->maparr[i - 1]);
		ft_split_free(line);
		free((*node)->line);
		tmp = (*node);
		(*node) = (*node)->next;
		free(tmp);
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
		ft_exit("Error\n: Failed to Read Map\n", 1, f);
	convert_list_to_array(&node, f);
	ft_validate_map(f);
	return (0);
}
