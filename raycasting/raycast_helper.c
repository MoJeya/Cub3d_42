#include "../cub3d.h"

void	set_startval(int x, t_gen_info *info)
{
	t_point	view;

	view.x = (info->player.plane.x * info->raycast.camera_x);
	view.y = (info->player.plane.y * info->raycast.camera_x);
	info->hit = 0;
	info->player.step_x = 1;
	info->raycast.camera_x = (double)(2 * x) / (double)SCREEN_W - 1;
	info->raycast.dir.x = info->player.dir.x + view.x;
	info->raycast.dir.y = info->player.dir.y + view.y;
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
}

void	set_line_height(t_gen_info *info)
{
	info->line_h = (int)(SCREEN_H / info->player.prep_wall_dist);
	info->raycast.draw_start = -info->line_h / 2 + SCREEN_H / 2;
	info->raycast.draw_end = info->line_h / 2 + SCREEN_H / 2;
	if (info->raycast.draw_end >= SCREEN_H)
		info->raycast.draw_end = SCREEN_H - 1;
}