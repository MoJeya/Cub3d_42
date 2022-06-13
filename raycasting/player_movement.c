/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:50:42 by rschleic          #+#    #+#             */
/*   Updated: 2022/06/13 14:51:44 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	vertical(t_gen_info *info, int p)
{
	double	movment_speed;
	int		i;
	int		end_value;
	t_point	p_dir;

	movment_speed = info->frame.movment_speed;
	i = 0;
	end_value = 5;
	p_dir.x = info->player.dir.x;
	p_dir.y = info->player.dir.y;
	if (p == -1)
	{
		i = -5;
		end_value = 0;
	}
	if (check_for_wall(info, i, end_value, info->player.dir))
	{
		info->player.pos.y += p_dir.y * p * info->frame.movment_speed;
		info->player.pos.x += p_dir.x * p * info->frame.movment_speed;
	}
}

static void	horizontal(t_gen_info *info, int p)
{
	double	movment_speed;
	int		i;
	int		end_value;

	movment_speed = info->frame.movment_speed;
	i = 0;
	end_value = 5;
	if (p == -1)
	{
		i = -5;
		end_value = 0;
	}
	if (check_for_wall(info, i, end_value, info->player.plane))
	{
		info->player.pos.x += info->player.plane.x * p * movment_speed;
		info->player.pos.y += info->player.plane.y * p * movment_speed;
	}
}

void	player_movment(t_gen_info *info)
{	
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
	{
		mlx_delete_image(info->mlx, info->m_img);
		mlx_close_window(info->mlx);
		return ;
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
		rotate_player(info, 1);
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
		rotate_player(info, -1);
	if (mlx_is_mouse_down(info->mlx, MLX_MOUSE_BUTTON_LEFT))
		rotate_mouse(info);
	if (mlx_is_key_down(info->mlx, MLX_KEY_W))
		vertical(info, 1);
	if (mlx_is_key_down(info->mlx, MLX_KEY_S))
		vertical(info, -1);
	if (mlx_is_key_down(info->mlx, MLX_KEY_D))
		horizontal(info, 1);
	if (mlx_is_key_down(info->mlx, MLX_KEY_A))
		horizontal(info, -1);
}
