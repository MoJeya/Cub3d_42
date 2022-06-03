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

static bool	check_wall_horizontal(t_gen_info *info, int p)
{
	double movment_speed;
	t_point p_pos;
	t_point p_plane;
	t_point vec;

	movment_speed = info->frame.movment_speed * p;
	p_pos.x = info->player.pos.x;
	p_pos.y = info->player.pos.y;
	p_plane.x = info->player.dir.x;
	p_plane.y = info->player.dir.y;
	vec.x = p_pos.x-0.5 + p_plane.x * movment_speed;
	vec.y = p_pos.y-0.5 + p_plane.y * movment_speed;
	if (info->map[(int)vec.y][(int)vec.x] != '1'
	&& ((int)vec.y < info->map_y && (int)vec.x < info->map_x)
	&& ((int)vec.x > 0 && (int)vec.y > 0))
	{
		if (p == 1)
		{
			info->player.pos.y += info->player.plane.y * info->frame.movment_speed;
			info->player.pos.x += info->player.plane.x * info->frame.movment_speed;
		}
		else if (p == -1)
		{
			info->player.pos.y -= info->player.plane.y * info->frame.movment_speed;
			info->player.pos.x -= info->player.plane.x * info->frame.movment_speed;
		}
		return (true);
	}
	return (false);   
}

void	player_movment(t_gen_info *info, int map_posx, int map_posy)
{
	t_point vec;
	vec.x += info->player.pos.x + info->player.plane.x * info->frame.movment_speed;
	vec.y += info->player.pos.y + info->player.plane.y * info->frame.movment_speed;
	if (info->map[map_posy][map_posx] != '1')
	{
		if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
			rotate_player(info, 1);
		if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
			rotate_player(info, -1);
	}
	else
	{

		// printf("map max val:\n x = %d\ny = %d\n", info->map_x, info->map_y);
		// printf("player movement:\n\tx:\t%f\n\ty:\t%f\n", vec.x, vec.y);
		printf("real map pos:\nx:%d\ny:%d\n",map_posx, map_posy);
		// printf("info->dir.x: %f\ninfo->dir.y: %f\n", info->player.dir.x, info->player.dir.y);
		// printf("info->plane.x: %f\ninfo->plane.y: %f\n", info->player.plane.x, info->player.plane.y);
	}
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
		check_wall_horizontal(info, 1);
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_A))
	{
		check_wall_horizontal(info, -1);
	}
}
