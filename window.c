/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:42:57 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/05/09 09:42:35 by rschleic         ###   ########.fr       */
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

void creat_map(mlx_t *mlx, mlx_image_t *img, t_gen_info *info)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < info->map_y)
	{
		x = 0;
		while(x < info->map_x)
		{
			if (info->map[y][x] == '1')
			{
				creat_tile(img);
				mlx_image_to_window(mlx, img, y+25, x+25);
			}
			x++;
		}
		y++;
	}
}

int32_t	create_window(mlx_t *mlx, mlx_image_t *panel, t_gen_info *info)
{
	mlx_image_t *tiles;

	tiles = NULL;
	mlx = mlx_init(info->win_x, info->win_y, "CUBE3D", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	panel = mlx_new_image(mlx, info->win_x, info->win_y);//dass canvas für denn pixel
	tiles = mlx_new_image(mlx, TILES_W, TILES_H);
	memset(panel->pixels, 0, panel->width * panel->height * sizeof(int));
	// memset(tiles->pixels, 250, tiles->width * tiles->height * sizeof(int));
	creat_map(mlx, tiles, info);
	// creat_tile(tiles);
	// printf("%d\n", tiles->width);
	mlx_image_to_window(mlx, panel, 0, 0); //adds render quoe
	mlx_image_to_window(mlx, tiles, 0, 0);
	// mlx_image_to_window(mlx, tiles, 36, 0);
	// mlx_put_pixel(tiles, WINDOW_X/2, WINDOW_Y/2, 0xFFFFFFFF);
	// mlx_delete_image(mlx, tiles);
	// mlx_image_to_window(mlx, g_img, 0, 0);
	// mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

