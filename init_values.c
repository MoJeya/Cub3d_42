/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:19:03 by rschleic          #+#    #+#             */
/*   Updated: 2022/06/11 19:04:11 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_textures(t_gen_info *info)
{
	int	i;

	i = 0;
	info->xpm[0] = mlx_load_xpm42(info->texture_no_path);
	info->xpm[1] = mlx_load_xpm42(info->texture_so_path);
	info->xpm[2] = mlx_load_xpm42(info->texture_we_path);
	info->xpm[3] = mlx_load_xpm42(info->texture_ea_path);
	if (!info->xpm[0] || !info->xpm[1] || !info->xpm[2] || !info->xpm[3])
		return (0);
	info->m_wall = mlx_load_png("./minimap/img/dungeon.png");
	info->player_img = mlx_load_png("./minimap/img/person.png");
	info->back_g = mlx_load_png("./minimap/img/playground.png");
	return (1);
}

void	init_genaral_info(t_gen_info *info)
{
	info->map_x = 0;
	info->map_y = 0;
	info->win_x = 0;
	info->win_y = 0;
	info->ceiling.set = false;
	info->ceiling.red = 0;
	info->ceiling.yellow = 0;
	info->ceiling.blue = 0;
	info->floor.set = false;
	info->floor.red = 0;
	info->floor.yellow = 0;
	info->floor.blue = 0;
	info->path = NULL;
	info->side = 0;
	info->player.step_x = 0;
	info->player.step_y = 0;
	info->raycast.camera_x = 0;
	info->frame.old_time = 0;
	info->frame.frame_time = 0;
	info->side = 0;
	info->success = 0;
	info->check[0] = false;
	info->check[1] = false;
	info->check[2] = false;
	info->check[3] = false;
}

static void	player_north_view(t_gen_info *info)
{
	info->player.dir.x = 0;
	info->player.dir.y = -1;
	info->player.plane.x = -0.66;
	info->player.plane.y = 0;
	info->texture_no_path = NULL;
	info->texture_so_path = NULL;
	info->texture_we_path = NULL;
	info->texture_ea_path = NULL;
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
