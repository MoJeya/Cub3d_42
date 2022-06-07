
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

bool	check_side_wall(t_gen_info *info, int i, int end_value)
{	
	t_point	plane;
	t_point	pos;

	plane = info->player.plane;
	pos = info->player.pos;
	while (i < end_value)
	{
		info->raycast.dir.x = info->player.dir.x;
		info->raycast.dir.y = info->player.dir.y;
		if (info->map[(int)(pos.y + plane.y * i * info->frame.movment_speed)]
			[(int)(pos.x + plane.x * i * info->frame.movment_speed)] == '1')
			return (false);
		i++;
	}
	return (true);
}

static void	horizontal(t_gen_info *info, int p)
{
	double	movment_speed;
	int		i;
	int		end_value;

	movment_speed = info->frame.movment_speed;
	end_value = 0;
	i = 0;
	if (p == -1)
	{
		i = -5;
		end_value = 0;
	}
	else if (p == 1)
	{
		i = 0;
		end_value = 5;
	}
	if (check_side_wall(info, i, end_value))
	{
		info->player.pos.x += info->player.plane.x * p * movment_speed;
		info->player.pos.y += info->player.plane.y * p * movment_speed;
	}
}

void	player_movment(t_gen_info *info)
{	
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
		check_wall_vertical(info, 1);
	if (mlx_is_key_down(info->mlx, MLX_KEY_S))
		check_wall_vertical(info, -1);
	if (mlx_is_key_down(info->mlx, MLX_KEY_D))
		horizontal(info, 1);
	if (mlx_is_key_down(info->mlx, MLX_KEY_A))
		horizontal(info, -1);
}
