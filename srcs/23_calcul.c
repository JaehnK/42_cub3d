/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   23_calcul.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:29:53 by kjung             #+#    #+#             */
/*   Updated: 2025/02/20 16:47:50 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc(t_cub *cub)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ft_init_player_view();
		while (cub->ray.hit == 0)
		{
			ft_hit_checker();
		}
		ft_calc_perp_wall_dist();
		ft_calc_texture();
		ft_adapt_texture();
		x++;	
	}
}
