/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_calculation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehukim <jaehukim42@student.42gyeong      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:49:46 by jaehukim          #+#    #+#             */
/*   Updated: 2025/02/19 12:49:47 by jaehukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main_loop(t_cub **cub)
{
	static int	frame_count;

	frame_count++;
	if (frame_count == 1)
		printf("First frame rendering started\n");
	calc(*cub);
	draw(*cub);
	if (frame_count == 1)
		printf("First frame completed\n");
	return (0);
}
