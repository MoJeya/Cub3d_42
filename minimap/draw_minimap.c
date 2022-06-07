/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:55:30 by rschleic          #+#    #+#             */
/*   Updated: 2022/06/07 20:23:53 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_minimap(t_gen_info *info)
{
	int	x;
	int	y;
	int	x_tile;
	int	y_tile;

	x = 0;
	y = 0;
	y_tile = 0;
	while (y < info->map_y)
	{
		x = 0;
		x_tile = SCREEN_W - (info->map_x - 1) * TILES_W;
		while (x < info->map_x)
		{
			if (info->map[y][x] == '1')
				mlx_draw_texture(info->m_img, info->m_wall, x_tile, y_tile);
			if (info->map[y][x] == '0')
				mlx_draw_texture(info->m_img, info->back_g, x_tile, y_tile);
			x_tile += TILES_W;
			x++;
		}
		y_tile += TILES_H;
		y++;
	}
	minimap_movement(info);
}

void	minimap_movement(t_gen_info *info)
{
	int	mini_x;
	int	mini_y;

	mini_x = ((info->player.pos.x / info->map_x) * (info->map_x * TILES_W)
			+ SCREEN_W - (info->map_x * TILES_W)) - TILES_W / 2;
	mini_y = ((info->player.pos.y / info->map_y) * (info->map_y * TILES_H)
			- TILES_H / 2);
	mlx_draw_texture(info->m_img, info->player_img, mini_x + TILES_W, mini_y);
}
