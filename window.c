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
//A: Funcrion um farbwerte zu setten, von der alten MLX

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

void creat_player(mlx_image_t *player, int x_tile, int y_tile)
{
	int x;
	int	y;

	x = 0;
	y = 0;
	while (x < TILES_W)
	{
		y = 0;
		while (y < TILES_H)
		{
			mlx_put_pixel(player, x + x_tile, y + y_tile, 0xAEEEEE);
			y++;
		}
		x++;
	}
}

void creat_map(t_gen_info *info, mlx_image_t *tiles)
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
			if (info->map[y][x] != ' ' && !ft_strchr("NESW", info->map[y][x]))
				creat_tile(tiles, x*25, y*25, info->map[y][x] - '0');
			if (info->map[y][x] == '\0')
				break;
			x++;
		}
		y++;
	}
}

bool wall_checker(t_gen_info *info)
{
	int p_pos_x;
	int p_pos_y;

	p_pos_x = info->player.p_pos.x;
	p_pos_y = info->player.p_pos.y;
	if (ft_strchr("1 ", info->map[p_pos_y][p_pos_x]))
	{
		return (false);
	}
	else
		return (true);

}

void player_movment(void *param)
{
	t_gen_info *info;

	info = param;
	int tmp;

	tmp = 0;
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
	if (mlx_is_key_down(info->mlx, MLX_KEY_W))
	{
		tmp = info->player.p_pos.y;
		if (info->player.p_pos.y-1 >= 0)
		{
			info->player.p_pos.y -=1;
			if (wall_checker(info))
				info->player.p_img->instances[0].y -= TILES_H;
			else
				info->player.p_pos.y = tmp;
		}
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_S))
	{
		tmp = info->player.p_pos.y;
		if (info->player.p_pos.y+1 < info->map_y)
		{
			info->player.p_pos.y +=1;
			if (wall_checker(info))
				info->player.p_img->instances[0].y += TILES_H;
			else
				info->player.p_pos.y = tmp;
		}
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_A))
	{
		tmp = info->player.p_pos.x;
		if (info->player.p_pos.x-1 >= 0)
		{
			info->player.p_pos.x -= 1;
			if (wall_checker(info))
				info->player.p_img->instances[0].x -= TILES_W;
			else
				info->player.p_pos.x = tmp;
		}
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_D))
	{
		tmp = info->player.p_pos.x;
		if (info->player.p_pos.x+1 < info->map_x)
		{
			info->player.p_pos.x+=1;
			if (wall_checker(info))
				info->player.p_img->instances[0].x += TILES_W;
			else
				info->player.p_pos.x = tmp;
		}
	}
	
}

int32_t	create_window(t_gen_info *info)
{
	mlx_image_t *tiles;

	tiles = NULL;
	info->mlx = mlx_init(info->win_x, info->win_y, "CUBE3D", true);
	if (!info->mlx)
		exit(EXIT_FAILURE);
	tiles = mlx_new_image(info->mlx, TILES_W * info->map_x, TILES_H * info->map_y);
	info->player.p_img = mlx_new_image(info->mlx, info->win_x, info->win_y);
	creat_map(info, tiles);
	creat_player(info->player.p_img, info->player.p_pos.x*25, info->player.p_pos.y*25);
	mlx_image_to_window(info->mlx, tiles, 0, 0);
	mlx_image_to_window(info->mlx, info->player.p_img, 0, 0);
	// mlx_delete_image(mlx, tiles);
	mlx_loop_hook(info->mlx, &player_movment, info);
	mlx_loop(info->mlx);
	mlx_terminate(info->mlx);
	return (EXIT_SUCCESS);
}
