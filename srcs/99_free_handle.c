/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_free_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:06:38 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/22 19:09:47 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_split_free(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i++]);
	}
	free(arr);
}

void	free_maparr(t_file **file)
{
	int	i;

	i = 0;
	while ((*file)->maparr[i])
		free((*file)->maparr[i++]);
	free((*file)->maparr);
}

void	free_file_struct(t_file **file)
{
	if (!(*file))
		return ;
	if (((*file))->filename)
		free((*file)->filename);
	if ((*file)->no_dir)
		free((*file)->no_dir);
	if ((*file)->so_dir)
		free((*file)->so_dir);
	if ((*file)->we_dir)
		free((*file)->we_dir);
	if ((*file)->ea_dir)
		free((*file)->ea_dir);
	if ((*file)->f_dir)
		free((*file)->f_dir);
	if ((*file)->c_dir)
		free((*file)->c_dir);
	if ((*file)->maparr)
		free_maparr(file);
	free(*file);
	(*file) = NULL;
}

void	ft_exit(char *msg, int exit_num, t_file **f)
{
	free_file_struct(f);
	ft_putstr_fd(msg, 2);
	exit(exit_num);
}
