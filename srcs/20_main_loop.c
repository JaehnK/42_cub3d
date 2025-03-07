/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_main_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:49:46 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/22 18:24:42 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main_loop(t_cub **cub)
{
	static int	frame_count;

	frame_count++;
	calc(*cub);
	draw(*cub);
	return (0);
}
