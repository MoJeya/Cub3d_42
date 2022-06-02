#include "../cub3d.h"

void rotate_player(t_gen_info *info, int dir)
{
    t_point old_dir;
    t_point old_plane;

    old_dir = info->player.dir;
    old_plane = info->player.plane;
    info->frame.rotation_speed *= dir;
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
        return (true);
    return (false);
}

static bool check_wall_horizontal(t_gen_info *info, int p)
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
    vec.x = p_pos.x + p_plane.x * movment_speed;
    vec.y = p_pos.y + p_plane.y * movment_speed;
    if (info->map[(int)vec.y][(int)vec.x] != '1')
        return (true);
    return (false);   
}

void player_movment(t_gen_info *info)
{
    //bis hier hin wurde alles mit dem window erledigt 

    if(mlx_is_mouse_down(info->mlx, MLX_MOUSE_BUTTON_LEFT))
        rotate_mouse(info);
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
    {
        mlx_delete_image(info->mlx, info->m_img);
		mlx_close_window(info->mlx);
        return ;
    }
	if (mlx_is_key_down(info->mlx, MLX_KEY_W))
	{
        if (check_wall_vertical(info, 1))
        {
            info->player.pos.y += info->player.dir.y * info->frame.movment_speed;
            info->player.pos.x += info->player.dir.x * info->frame.movment_speed;
        }
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_S))
	{
        if(check_wall_vertical(info, -1))
        {
            info->player.pos.y -= info->player.dir.y * info->frame.movment_speed;
            info->player.pos.x -= info->player.dir.x * info->frame.movment_speed;
        }
	}
    if (mlx_is_key_down(info->mlx, MLX_KEY_D))
    {
        if (check_wall_horizontal(info, 1))
        {
            info->player.pos.y += info->player.plane.y * info->frame.movment_speed;
            info->player.pos.x += info->player.plane.x * info->frame.movment_speed;
        }
    }
    if (mlx_is_key_down(info->mlx, MLX_KEY_A))
    {
        if (check_wall_horizontal(info, -1))
        {
            info->player.pos.y -= info->player.plane.y * info->frame.movment_speed;
            info->player.pos.x -= info->player.plane.x * info->frame.movment_speed;
        }
    }
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
	{
        rotate_player(info, 1);
	}   
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
	{
        rotate_player(info, -1);
	}
}
