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

//wtf was ist das?
//A: Funcrion um farbwerte zu setten, von der alten MLX
//TODO: IMAGE ROTTION HERAUSFINDEN

void creat_tile(mlx_image_t *tile, int x_tile, int y_tile, int color, t_gen_info *info)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < TILES_W-1)
	{
		y = 0;
		while (y < TILES_H-1)
		{
			if (color == 1)
				mlx_put_pixel(tile, x + x_tile, y + y_tile, 0xFFFFFFFF);
			if (color == 0 || (color >= 17 && color <= 42))
				mlx_put_pixel(tile, x + x_tile, y + y_tile, 0x444444);

			y++;
		}
		x++;
	}
	(void)info;
}

// void player_rotation()
void creat_player(mlx_image_t *player, int x_tile, int y_tile)
{
	int x;
	int	y;
	int line;

	x = 0;
	y = 0;
	while (x < 5)
	{
		y = 0;
		while (y < 5)
		{
			mlx_put_pixel(player, x + x_tile, y + y_tile, 0xAEEEEE);
			y++;
		}
		x++;
	}
	y = 4;
	line = 0;
	while (line < 8)
	{
		mlx_put_pixel(player, 2 + x_tile, y + y_tile, 0xAEEEEE);
		line++;
		y++;
	}
}

void creat_map(t_gen_info *info, mlx_image_t *tiles)
{
	int x;
	int y;
	int xo;
	int yo;

	y = 0;
	while (y < info->map_y)
	{
		x = 0;
		// printf("	y: %d -> map y: %d!\n", y, info->map_y);
		while(x < info->map_x)
		{
			// printf("x: %d -> map x: %d\n", x, info->map_x);
			xo = x * TILES_W;
			yo = y * TILES_H;
			if (info->map[y][x] != ' ')
				creat_tile(tiles, xo, yo, info->map[y][x] - '0', info);
			if (info->map[y][x] == '\0')
				break;
			x++;
		}
		y++;
	}
}

void	get_textures(t_gen_info *info)
{
	int i;

	i = 0;

		info->xpm[0] = mlx_load_xpm42(info->texture_no_path);
		info->xpm[1] = mlx_load_xpm42(info->texture_so_path);
		info->xpm[2] = mlx_load_xpm42(info->texture_we_path);
		info->xpm[3] = mlx_load_xpm42(info->texture_ea_path);

		// info->text_img[i] = mlx_texture_to_image(info->mlx, &info->xpm[i]->texture);
}

int32_t	create_window(t_gen_info *info)
{
	mlx_image_t *txt_img = NULL;
	
	info->mlx = mlx_init(screenWidth, screenHeight, "CUBE3D", true);//wie wurde des berechnet, bzw warum passt es genau so von der grösse???
	if (!info->mlx)
		exit(EXIT_FAILURE);
	get_textures(info);
	txt_img = mlx_texture_to_image(info->mlx, &info->xpm[0]->texture);
	info->m_img = mlx_new_image(info->mlx, screenWidth, screenHeight);
	printf("map size:\nx\t%d\ny:\t%d\n", info->map_x, info->map_y);
// load xpm to an image
//go to taht image
	mlx_image_to_window(info->mlx, txt_img, 0, 0);
	mlx_loop_hook(info->mlx, &player_movment, info);//nach dem fpointer kommen die values
	mlx_loop(info->mlx);
	mlx_terminate(info->mlx);
	return (EXIT_SUCCESS);
}
//wie greifen die functions ineinander, welche kommt zuerst, etc... 
//würde gerne erklären können, was da genau passiert

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

