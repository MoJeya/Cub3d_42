#include "../cub3d.h"

void rotate_player(t_gen_info *info, int dir)
{
	t_point old_dir;
	t_point old_plane;
	// t_point	check_side;
	old_dir = info->player.dir;
	old_plane = info->player.plane;
	info->frame.rotation_speed *= dir;
	// check_side.x = info->player.dir.x * cos(info->frame.rotation_speed) - info->player.dir.y * sin(info->frame.rotation_speed);
	// check_side.y =  old_dir.x * sin(info->frame.rotation_speed) + info->player.dir.y * cos(info->frame.rotation_speed);
	info->player.dir.x = info->player.dir.x * cos(info->frame.rotation_speed) - info->player.dir.y * sin(info->frame.rotation_speed);
	info->player.dir.y = old_dir.x * sin(info->frame.rotation_speed) + info->player.dir.y * cos(info->frame.rotation_speed);
	info->player.plane.x = info->player.plane.x * cos(info->frame.rotation_speed) - info->player.plane.y * sin(info->frame.rotation_speed);
	info->player.plane.y = old_plane.x * sin(info->frame.rotation_speed) + info->player.plane.y * cos(info->frame.rotation_speed);
}

void    rotate_mouse(t_gen_info *info)
{
	int         old_mouse_x;
	int         old_mouse_y;

	old_mouse_x = info->mouse_x;
	old_mouse_y = info->mouse_y;
	mlx_get_mouse_pos(info->mlx, &info->mouse_x, &info->mouse_y);
	if (info->mouse_x > old_mouse_x)//rechts shift
		rotate_player(info, -1);
	if (info->mouse_x < old_mouse_x)// links shift
		rotate_player(info, 1);
}

static bool check_wall_vertical(t_gen_info *info, int p)
{
	double  movment_speed;
	t_point p_pos;
	t_point p_dir;
	t_point vec;

	movment_speed = info->frame.movment_speed * p;
	p_pos.x = info->player.pos.x;
	p_pos.y = info->player.pos.y;
	p_dir.x = info->player.dir.x;
	p_dir.y = info->player.dir.y;
	vec.y = p_pos.y + p_dir.y * movment_speed;
	vec.x = p_pos.x + p_dir.x * movment_speed;
	if (info->map[(int)vec.y][(int)vec.x] != '1')
	{
		if (p == 1)
		{
			info->player.pos.y += info->player.dir.y * info->frame.movment_speed;
			info->player.pos.x += info->player.dir.x * info->frame.movment_speed;
		}
		else if (p == -1)
		{
			info->player.pos.y -= info->player.dir.y * info->frame.movment_speed;
			info->player.pos.x -= info->player.dir.x * info->frame.movment_speed;
		}
		return (true);
	}
	return (false);
}

/**
 ** Old Movment horizontal calculation
 * info->player.pos.y += info->player.plane.y * info->frame.movment_speed;
 * info->player.pos.x += info->player.plane.x * info->frame.movment_speed;
*/

bool check_side_wall(t_gen_info *info, int p)
{
	int i;
	t_point plane;
	// t_point vec;

	plane  = info->player.plane;
	if (p == -1)
	{
		i = -5;
		while (i < 0)
		{
			info->raycast.dir.x = info->player.dir.x;
			info->raycast.dir.y = info->player.dir.y;
			if (info->map[(int)(info->player.pos.y + plane.y * i * info->frame.movment_speed)][(int)(info->player.pos.x + plane.x * i * info->frame.movment_speed)] == '1')
				return (false);
			i++;
		}
	}
	else if (p == 1)
	{
		i = 0;
		while (i < 5)
		{
			info->raycast.dir.x = info->player.dir.x;
			info->raycast.dir.y = info->player.dir.y;
			if (info->map[(int)(info->player.pos.y + plane.y * i * info->frame.movment_speed)][(int)(info->player.pos.x + plane.x * i * info->frame.movment_speed)] == '1')
				return (false);
			i++;
		}
	}

	return (true);
}

static void	check_wall_horizontal(t_gen_info *info, double dir_x, double dir_y, int p)
{
	double movment_speed;
	t_point p_pos;
	t_point vec;

	movment_speed = info->frame.movment_speed;
	p_pos = info->player.pos;
	vec.x = p_pos.x + info->player.plane.x * dir_x * p * movment_speed;
	vec.y = p_pos.y + info->player.plane.y * dir_y * p * movment_speed;
	// printf("x: %f\ny: %f\nmap: %c\n", info->player.dir.x, info->player.dir.y, info->map[(int)vec.x][(int)vec.y]);
	if (check_side_wall(info, p))
	{
		// printf("PLAYER\nx:%f\ny:%f\n", info->player.pos.x, info->player.pos.y);
		info->player.pos.x += info->player.plane.x * p * movment_speed;
		info->player.pos.y += info->player.plane.y * p * movment_speed;
	}
}

void	player_movment(t_gen_info *info)
{
	t_point vec;
	vec.x += info->player.pos.x + info->player.plane.x * info->frame.movment_speed;
	vec.y += info->player.pos.y + info->player.plane.y * info->frame.movment_speed;
	
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
		rotate_player(info, 1);
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
		rotate_player(info, -1);
	if (mlx_is_mouse_down(info->mlx, MLX_MOUSE_BUTTON_LEFT))
		rotate_mouse(info);
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
	{
		mlx_delete_image(info->mlx, info->m_img);
		mlx_close_window(info->mlx);
		return ;
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_W))
	{
		check_wall_vertical(info, 1);
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_S))
	{
		check_wall_vertical(info, -1);
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_D))
	{
		check_wall_horizontal(info, info->raycast.dir.x, info->raycast.dir.y, 1);
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_A))
	{
		check_wall_horizontal(info, info->raycast.dir.x, info->raycast.dir.y, -1);
	}
}
