/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:42:57 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/06/03 18:46:34 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	create_window(t_gen_info *info)
{
	info->mlx = mlx_init(SCREEN_W, SCREEN_H, "CUBE3D", true);
	if (!info->mlx)
		exit(EXIT_FAILURE);
	info->m_img = mlx_new_image(info->mlx, SCREEN_W, SCREEN_H);
	mlx_image_to_window(info->mlx, info->m_img, 0, 0);
	mlx_get_mouse_pos(info->mlx, &info->mouse_x, &info->mouse_y);
	draw_minimap(info);
	mlx_loop_hook(info->mlx, &render_wrld, info);
	mlx_loop(info->mlx);
	mlx_terminate(info->mlx);
	mlx_delete_image(info->mlx, info->m_img);
	return (EXIT_SUCCESS);
}
