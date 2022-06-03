/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:42:57 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/05/14 20:57:04 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

int32_t	create_window(t_gen_info *info)
{
	
	info->mlx = mlx_init(screenWidth, screenHeight, "CUBE3D", true);//wie wurde des berechnet, bzw warum passt es genau so von der grösse???
	if (!info->mlx)
		exit(EXIT_FAILURE);
		//check
	// txt_img = mlx_texture_to_image(info->mlx, &info->xpm[0]->texture);
	//gibts nicht bei Tam
	info->m_img = mlx_new_image(info->mlx, screenWidth, screenHeight);
	//check
	// printf("map size:\nx\t%d\ny:\t%d\n", info->map_x, info->map_y);
	// printf("Player pos x: %f\nplayer pos y: %f\n", info->player.pos.x, info->player.pos.y);
// load xpm to an image
//go to taht image
	mlx_image_to_window(info->mlx, info->m_img, 0, 0);
	mlx_get_mouse_pos(info->mlx, &info->mouse_x, &info->mouse_y);
	draw_minimap(info);
	mlx_loop_hook(info->mlx, &render_wrld, info);//nach dem fpointer kommen die values
	// mlx_cursor_hook(info->mlx, func(xpos, ypos, NULL), NULL)
	mlx_loop(info->mlx);
	//check
	//bis hierhin ist der Aufabu korrekt
	mlx_terminate(info->mlx);
	mlx_delete_image(info->mlx, info->m_img);
	return (EXIT_SUCCESS);
}

/**BONUS PART ACTIVATE LATER
	// tiles = mlx_new_image(info->mlx, info->map_x * TILES_W, info->map_y * TILES_H);
	// info->player.p_img = mlx_new_image(info->mlx, info->win_x, info->win_y);
	// creat_map(info, tiles);
	// creat_player(info->player.p_img, info->player.pos.x * TILES_W, info->player.pos.y * TILES_H);
	// mlx_image_to_window(info->mlx, tiles, 0, 0);
	// mlx_image_to_window(info->mlx, info->player.p_img, 0, 0);
	// mlx_delete_image(mlx, tiles);
	// mlx_loop_hook(info->mlx, &player_movment, info);
*/
