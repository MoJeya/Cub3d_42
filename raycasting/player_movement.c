
#include "../cub3d.h"

static bool	vertical(t_gen_info *info, int p)
{
	double	movment_speed;
	t_point	p_pos;
	t_point	p_dir;
	t_point	vec;

	movment_speed = info->frame.movment_speed * p;
	p_pos.x = info->player.pos.x;
	p_pos.y = info->player.pos.y;
	p_dir.x = info->player.dir.x;
	p_dir.y = info->player.dir.y;
	vec.y = p_pos.y + p_dir.y * movment_speed;
	vec.x = p_pos.x + p_dir.x * movment_speed;
	if (info->map[(int)vec.y][(int)vec.x] != '1')
	{
		info->player.pos.y += p_dir.y * p * info->frame.movment_speed;
		info->player.pos.x += p_dir.x * p * info->frame.movment_speed;
		return (true);
	}
	return (false);
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
		vertical(info, 1);
	if (mlx_is_key_down(info->mlx, MLX_KEY_S))
		vertical(info, -1);
	if (mlx_is_key_down(info->mlx, MLX_KEY_D))
		horizontal(info, 1);
	if (mlx_is_key_down(info->mlx, MLX_KEY_A))
		horizontal(info, -1);
}
