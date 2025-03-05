/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spacejump.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:24:31 by kjung             #+#    #+#             */
/*   Updated: 2025/02/26 17:41:46 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spacetrim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:24:31 by kjung             #+#    #+#             */
/*   Updated: 2025/02/26 17:35:26 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_space_len_front(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t')
			i++;
		else
			break ;
	}
	return (i);
}

size_t	ft_space_len_back(char *s)
{
	int	i;
	int	len;

	len = ft_strlen(s);
	if (len == 0)
		return (0);
	i = len - 1;
	while (i >= 0)
	{
		if (s[i] == ' ' || s[i] == '\t')
			i--;
		else
			break ;
	}
	return (len - i - 1);
}

char	*ft_spacejump(char *s)
{
	size_t	front_spaces;
	size_t	back_spaces;
	size_t	new_len;
	size_t	idx;
	char	*res;

	if (!s)
		return (NULL);
	front_spaces = ft_space_len_front(s);
	if (front_spaces == ft_strlen(s))
		return (ft_strdup(""));
	back_spaces = ft_space_len_back(s);
	new_len = ft_strlen(s) - front_spaces - back_spaces;
	res = (char *) malloc(sizeof(char) * (new_len + 1));
	if (!res)
		return (NULL);
	idx = 0;
	while (idx < new_len)
	{
		res[idx] = s[front_spaces + idx];
		idx++;
	}
	res[idx] = '\0';
	return (res);
}
