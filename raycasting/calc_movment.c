/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_movment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:50:34 by rschleic          #+#    #+#             */
/*   Updated: 2022/06/13 14:51:36 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static double	rot_calc_x(t_gen_info *info)
{
	info->player.dir.x = info->player.dir.x * cos(info->frame.rotation_speed);
	return (info->player.dir.x);
}

static double	calc_p(t_gen_info *info)
{
	double	player_plx;

	player_plx = info->player.plane.x * cos(info->frame.rotation_speed);
	return (player_plx);
}

void	rotate_player(t_gen_info *info, int dir)
{
	t_point	old_dir;
	t_point	old_plane;
	double	new_plane_y;
	double	r_sp;

	r_sp = info->frame.rotation_speed;
	old_dir = info->player.dir;
	old_plane = info->player.plane;
	r_sp *= dir;
	info->player.dir.x = rot_calc_x(info) - info->player.dir.y * sin(r_sp);
	info->player.dir.y = old_dir.x * sin(r_sp) + info->player.dir.y * cos(r_sp);
	info->player.plane.x = calc_p(info) - info->player.plane.y * sin(r_sp);
	new_plane_y = info->player.plane.y;
	info->player.plane.y = old_plane.x * sin(r_sp) + new_plane_y * cos(r_sp);
}

void	rotate_mouse(t_gen_info *info)
{
	int	old_mouse_x;
	int	old_mouse_y;

	old_mouse_x = info->mouse_x;
	old_mouse_y = info->mouse_y;
	mlx_get_mouse_pos(info->mlx, &info->mouse_x, &info->mouse_y);
	if (info->mouse_x > old_mouse_x)
		rotate_player(info, -1);
	if (info->mouse_x < old_mouse_x)
		rotate_player(info, 1);
}

bool	check_for_wall(t_gen_info *info, int i, int end_value, t_point vec)
{
	t_point	pos;

	pos = info->player.pos;
	while (i < end_value)
	{
		info->raycast.dir.x = info->player.dir.x;
		info->raycast.dir.y = info->player.dir.y;
		if (info->map[(int)(pos.y + vec.y * i * info->frame.movment_speed)]
			[(int)(pos.x + vec.x * i * info->frame.movment_speed)] == '1')
			return (false);
		i++;
	}
	return (true);
}
