#include "../cub3d.h"

void	set_step(t_gen_info *info, int map_pos_x, int map_pos_y)
{
	if (info->raycast.dir.x < 0)
	{
		info->player.step_x = -1;
		info->raycast.side_dist.x = (info->player.pos.x
				- map_pos_x) * info->raycast.delta_dist.x;
	}
	else
	{
		info->player.step_x = 1;
		info->raycast.side_dist.x = (map_pos_x + 1.0
				- info->player.pos.x) * info->raycast.delta_dist.x;
	}
	if (info->raycast.dir.y < 0)
	{
		info->player.step_y = -1;
		info->raycast.side_dist.y = (info->player.pos.y
				- map_pos_y) * info->raycast.delta_dist.y;
	}
	else
	{
		info->player.step_y = 1;
		info->raycast.side_dist.y = (map_pos_y + 1.0
				- info->player.pos.y) * info->raycast.delta_dist.y;
	}
}

void	set_delta_dist(t_gen_info *info)
{
	if (info->raycast.dir.x == 0)
		info->raycast.delta_dist.x = INFINITY;
	else
		info->raycast.delta_dist.x = fabs(1 / info->raycast.dir.x);
	if (info->raycast.dir.y == 0)
		info->raycast.delta_dist.y = INFINITY;
	else
		info->raycast.delta_dist.y = fabs(1 / info->raycast.dir.y);
}

void	set_line_height(t_gen_info *info)
{
	info->line_h = (int)(SCREEN_H / info->player.prep_wall_dist);
	info->raycast.draw_start = -info->line_h / 2 + SCREEN_H / 2;
	info->raycast.draw_end = info->line_h / 2 + SCREEN_H / 2;
	if (info->raycast.draw_end >= SCREEN_H)
		info->raycast.draw_end = SCREEN_H - 1;
}

void	calc_perp_walldist(t_gen_info *info)
{
	t_point	side_dist;
	t_point	delta_dist;

	side_dist.x = info->raycast.side_dist.x;
	side_dist.y = info->raycast.side_dist.y;
	delta_dist.x = info->raycast.delta_dist.x;
	delta_dist.y = info->raycast.delta_dist.y;
	if (info->side == 0 || info->side == 1)
		info->player.prep_wall_dist = (side_dist.x - delta_dist.x);
	else if (info->side == 2 || info->side == 3)
		info->player.prep_wall_dist = (side_dist.y - delta_dist.y);
	set_line_height(info);
}

void	dda_calc(t_gen_info *info, int map_pos_x, int map_pos_y)
{
	while (info->hit == 0)
	{
		if (info->raycast.side_dist.x < info->raycast.side_dist.y)
		{
			info->raycast.side_dist.x += info->raycast.delta_dist.x;
			map_pos_x += info->player.step_x;
			if (info->raycast.dir.x < 0)
				info->side = 0;
			else
				info->side = 1;
		}
		else
		{
			info->raycast.side_dist.y += info->raycast.delta_dist.y;
			map_pos_y += info->player.step_y;
			if (info->raycast.dir.y < 0)
				info->side = 2;
			else
				info->side = 3;
		}
		if (info->map[map_pos_y][map_pos_x] > '0')
			info->hit = 1;
	}
}
