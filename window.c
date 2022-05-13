/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:42:57 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/05/13 18:04:48 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>
// void hook(void *param)
// {
//    data = param;
//    if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
// 		mlx_close_window(param);
// 	if (mlx_is_key_down(param, MLX_KEY_W))
// 		data->g_img.instances[0].y -= 5;
// 	if (mlx_is_key_down(param, MLX_KEY_S))
// 		data->g_img.instances[0].y += 5;
// 	if (mlx_is_key_down(param, MLX_KEY_A))
// 		data->g_img.instances[0].x -= 5;
// 	if (mlx_is_key_down(param, MLX_KEY_D))
// 		data->g_img.instances[0].x += 5;

// }

void creat_tile(mlx_image_t *tile)
{
	int x;
	int y;

	x = 0;
	y = 0;
	// (void)tile;
	while (x < TILES_W)
	{
		y = 0;
		while (y < TILES_H)
		{
			mlx_put_pixel(tile, x, y, 0xFFFFFFFF);
			y++;
		}
		x++;
	}
}

void creat_map(mlx_t *mlx, t_gen_info *info, mlx_image_t *tiles)
{
	int x;
	int y;
	int	right;
	int	down;

	// x = 0;
	y = 0;
	// (void)mlx;
	right = 0;
	down = y;
	while (y < info->map_y)
	{
		x = -1;
		while(x <= info->map_x)
		{
			if (info->map[y][x] == '1')
			{
				creat_tile(tiles);
				mlx_image_to_window(mlx, tiles, right, down);
				// mlx_image_to_window(mlx, img, y+25, x+25);
			}
			x++;
			right += 25;
		}
		y++;
		down += 25;
	}
}

int32_t	create_window(mlx_t *mlx, mlx_image_t *panel, t_gen_info *info)
{
	mlx_image_t *tiles;

	(void)panel;
	tiles = NULL;
	mlx = mlx_init(info->win_x, info->win_y, "CUBE3D", true);//blank window
	if (!mlx)
		exit(EXIT_FAILURE);
	// panel = mlx_new_image(mlx, info->win_x, info->win_y);//dass canvas für denn pixel in der grösse vom window - noch unsichtbar
	tiles = mlx_new_image(mlx, TILES_W, TILES_H);//canvas in der grösse von 25x25
	// memset(panel->pixels, 200, panel->width * panel->height * sizeof(int));//panel sichtbar machen, sozusagen eine pixel put
	// memset(tiles->pixels, 250, tiles->width * tiles->height * sizeof(int));
	creat_map(mlx, info, tiles);
	// creat_tile(tiles);
	// printf("%d\n", tiles->width);
	// mlx_image_to_window(mlx, panel, 0, 0); //adds render quoe//zieht das panel auf das window
	// mlx_image_to_window(mlx, tiles, 0, 0);
	// mlx_image_to_window(mlx, tiles, 25, 0);
	// mlx_put_pixel(tiles, WINDOW_X/2, WINDOW_Y/2, 0xFFFFFFFF);
	// mlx_delete_image(mlx, tiles);
	// mlx_image_to_window(mlx, g_img, 0, 0);
	// mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
//wir brauchen gar kein panel auf das wir extra zeichnen, die tiles reichen
// ohne mlx_image_to_window(mlx, tiles, 36, 0) gibt es nur die komische form von create tile()
// mit mlx_image_to_window(mlx, tiles, 36, 0) gibt es ein 25x25 tile
//so without create_map kein tile
//unser window ist eins zu lang in x richtung