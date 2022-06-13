/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:19:03 by rschleic          #+#    #+#             */
/*   Updated: 2022/06/13 15:55:51 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_textures(t_gen_info *info)
{
	int	i;

	i = 0;
	info->xpm[0] = mlx_load_xpm42(info->texture_no_path);
	info->xpm[1] = mlx_load_xpm42(info->texture_so_path);
	info->xpm[2] = mlx_load_xpm42(info->texture_we_path);
	info->xpm[3] = mlx_load_xpm42(info->texture_ea_path);
	if (!info->xpm[0] || !info->xpm[1] || !info->xpm[2] || !info->xpm[3])
	{
		error_free_exit("ERROR\ntexture path", info, INFO_MAP);
	}
	info->m_wall = mlx_load_png("./minimap/img/dungeon.png");
	info->player_img = mlx_load_png("./minimap/img/person.png");
	info->back_g = mlx_load_png("./minimap/img/playground.png");
	return (1);
}

static void	player_north_view(t_gen_info *info)
{
	info->player.dir.x = 0;
	info->player.dir.y = -1;
	info->player.plane.x = -0.66;
	info->player.plane.y = 0;
}

void	init_raycast_info(t_gen_info *info)
{
	player_north_view(info);
	if (info->player.looking == 'W')
	{
		info->player.dir.x = 1;
		info->player.dir.y = 0;
		info->player.plane.y = -0.66;
		info->player.plane.x = 0;
	}
	else if (info->player.looking == 'S')
	{
		info->player.dir.x = 0;
		info->player.dir.y = 1;
		info->player.plane.x = 0.66;
		info->player.plane.y = 0;
	}
	else if (info->player.looking == 'E')
	{
		info->player.dir.x = -1;
		info->player.dir.y = 0;
		info->player.plane.x = 0;
		info->player.plane.y = 0.66;
	}
}
