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

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
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
		printf("	y: %d -> map y: %d!\n", y, info->map_y);
		while(x < info->map_x)
		{
			printf("x: %d -> map x: %d\n", x, info->map_x);
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

bool wall_checker(double x, double y, t_gen_info *info)
{
	
	printf("char: %c\n", info->map[(int)y][(int)x]);
	if (info->map[(int)y][(int)x] == '1')
	{
		return (false);
	}
	if (info->map[(int)y][(int)x] == ' ')
		return (false);
	else
		return (true);

}

void ft_move_vert(t_gen_info *info, int dir)
{
	// double x;
	// double y;

	// x = info->player.p_pos.x;
	// y = info->player.p_pos.y + (1 * dir);
	// if (dir < 0)
	// {
	// 	info->player.p_img->instances[0].x += info->player.pos.delta_x;
	// 	info->player.p_img->instances[0].y += info->player.pos.delta_y;
	// }
	// else
	// {
	// 	info->player.p_img->instances[0].x -= info->player.pos.delta_x;
	// 	info->player.p_img->instances[0].y -= info->player.pos.delta_y;
	// }
	// if (wall_checker(x, y, info))
	// {
		// if (info->player.p_pos.x*)
		info->player.p_img->instances[0].y += (5 * dir);
		printf("player pos: x = %d | y = %d\n", info->player.p_img->instances[0].x, info->player.p_img->instances[0].y);
		// info->player.p_pos.y = y;
	// }
	(void)dir;

}

void ft_move_horizontal(t_gen_info *info, int dir)
{
	// double	x;
	// double	y;

	// x = info->player.p_pos.x + (1 * dir);
	// y = info->player.p_pos.y;
	// if (wall_check/er(x, y, info) && ((x * TILES_W) > info->player.p_img->instances[0].x))
	// {
		// if (dir < 0)
		// {
		// 	info->player.pos.angle -= 0.1;
		// 	info->player.p_img->instances[0].x -= cos(info->player.pos.angle) * 0.1;
		// 	info->player.p_img->instances[0].y -= sin(info->player.pos.angle) * 0.1;
		// }
		// else
		// {
		// 	info->player.pos.angle += 0.1;
		// 	info->player.p_img->instances[0].x += cos(info->player.pos.angle) * 0.1;
		// 	info->player.p_img->instances[0].y += sin(info->player.pos.angle) * 0.1;
		// }
		// if (info->player.pos.angle < 0)
		// {
		// 	info->player.pos.angle += 2 * PI;
		// }
		// }
		info->player.p_img->instances[0].x += (5 * dir);
		printf("player pos: x = %d | y = %d\n", info->player.p_img->instances[0].x, info->player.p_img->instances[0].y);
		// info->player.p_pos.x  = x;
		(void)dir;
	// }
}

void player_movment(void *param)
{
	t_gen_info *info;

	info = param;
	int tmp;

	tmp = 0;
	// printf("start value player pos:(%d | %d)\n", info->player.p_pos.x, info->player.p_pos.y);
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
	if (mlx_is_key_down(info->mlx, MLX_KEY_W))
	{
		ft_move_vert(info, -1);
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_S))
	{
		ft_move_vert(info, 1);
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_A))
	{
		// info->player.pos.angle -= 0.1;
		// if (info->player.pos.angle < 0)
		// {
		// 	info->player.pos.angle += 2 * PI;
		// }
		ft_move_horizontal(info, -1);
		// info->player.p_img->instances[0].x = cos(info->player.pos.angle) * 5;
		// info->player.p_img->instances[0].y = sin(info->player.pos.angle) * 5;
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_D))
	{
		// info->player.pos.angle += 0.1;
		// if (info->player.pos.angle > 2*PI)
		// {
		// 	info->player.pos.angle -= 2 * PI;
		// }
		// info->player.p_img->instances[0].x = cos(info->player.pos.angle) * 5;
		// info->player.p_img->instances[0].y = sin(info->player.pos.angle) * 5;
		ft_move_horizontal(info, 1);
	}
	// printf("end value player pos:(%d | %d)\n", info->player.p_pos.x, info->player.p_pos.y);
}

int32_t	create_window(t_gen_info *info)
{
	mlx_image_t *tiles;

	tiles = NULL;
	info->map_size_total = info->map_x * info->map_y;
	info->mlx = mlx_init(1024, 512, "CUBE3D", true);
	if (!info->mlx)
		exit(EXIT_FAILURE);
	tiles = mlx_new_image(info->mlx, info->map_x * TILES_W, info->map_y * TILES_H);
	info->player.p_img = mlx_new_image(info->mlx, info->win_x, info->win_y);
	creat_map(info, tiles);
	creat_player(info->player.p_img, info->player.pos.x * TILES_W, info->player.pos.y * TILES_H);
	mlx_image_to_window(info->mlx, tiles, 0, 0);
	mlx_image_to_window(info->mlx, info->player.p_img, 0, 0);
	// mlx_delete_image(mlx, tiles);
	mlx_loop_hook(info->mlx, &player_movment, info);
	mlx_loop(info->mlx);
	mlx_terminate(info->mlx);
	return (EXIT_SUCCESS);
}


/*
* if(map[y*mapX+x]== 1)
	{
		//farbe_1
	}
	else
		//farbe_2
*/