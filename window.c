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

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
//wtf was ist das?

void creat_tile(mlx_image_t *tile, int x_tile, int y_tile, int color)
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
			if (color == 1)
				mlx_put_pixel(tile, x + x_tile, y + y_tile, 0xFFFFFFFF);
			if (color == 0)
				mlx_put_pixel(tile, x + x_tile, y + y_tile, 0x444444);

			y++;
		}
		x++;
	}
}

void creat_map(__unused mlx_t *mlx, t_gen_info *info, mlx_image_t *tiles)
{
	int x;
	int y;
	int	right;
	int	down;

	y = 0;
	right = 0;
	down = y;
	while (y < info->map_y)
	{
		x = 0;
		right = 0;
		while(x <= info->map_x)
		{
			if (info->map[y][x] != ' ')
				creat_tile(tiles, x*25, y*25, info->map[y][x] - '0');
			if (info->map[y][x] == '\0')
				break;
			x++;
		}
		y++;
	}
}

int32_t	create_window(mlx_t *mlx, mlx_image_t *panel, t_gen_info *info)
{
	mlx_image_t *tiles;

	(void)panel;
	tiles = NULL;
	mlx = mlx_init(info->win_x, info->win_y, "CUBE3D", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	tiles = mlx_new_image(mlx, TILES_W * info->map_x, TILES_H * info->map_y);
	creat_map(mlx, info, tiles);
	mlx_image_to_window(mlx, tiles, 0, 0);
	// mlx_delete_image(mlx, tiles);
	// mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
