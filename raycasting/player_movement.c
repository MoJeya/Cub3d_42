#include "../cub3d.h"

bool map_hit(t_gen_info *info, int dir)
{
    if (dir > 0)
    {
        if (info->map[(int)(info->player.pos.y + info->player.dir.y * info->frame.movment_speed)][(int)info->player.pos.x] == '0')
            return (true);
        if (info->map[(int)info->player.pos.y][(int)(info->player.pos.x + info->player.dir.x * info->frame.movment_speed)] == '0')
            return (true);
    }
    else if (dir < 0)
    {
        if (info->map[(int)(info->player.pos.y - info->player.dir.y * info->frame.movment_speed)][(int)info->player.pos.x] == '0')
            return (true);
         if (info->map[(int)info->player.pos.y][(int)(info->player.pos.x - info->player.dir.x * info->frame.movment_speed)] == '0')
            return (true);   
    }
    return (false);
}

void move_vertical(t_gen_info *info, int dir)
{
    if (dir > 0)
    {
        if (map_hit(info, dir))
        {
            info->player.pos.y +=info->player.dir.y * info->frame.movment_speed;
            info->player.pos.x += info->player.dir.x * info->frame.movment_speed;
        }
    }
    else if (dir < 0)
    {
        if (map_hit(info, dir))
        {
            info->player.pos.y -= info->player.dir.y * info->frame.movment_speed;
            info->player.pos.x -= info->player.dir.x * info->frame.movment_speed;
        }
    }
}


void player_movment(void *param)
{
    //bis hier hin wurde alles mit dem window erledigt 
	t_gen_info *info;

	info = param;
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
    {
        mlx_delete_image(info->mlx, info->m_img);
		mlx_close_window(info->mlx);
        return ;
    }
	if (mlx_is_key_down(info->mlx, MLX_KEY_W))
	{
        if (((int)(info->player.pos.y + info->player.dir.y * info->frame.movment_speed) >= 0
            && (int)(info->player.pos.x + info->player.dir.x * info->frame.movment_speed) >= 0)
            && ((int)(info->player.pos.y + info->player.dir.y * info->frame.movment_speed) < info->map_y)
            && (int)(info->player.pos.x + info->player.dir.x * info->frame.movment_speed) < info->map_x)
        {
            move_vertical(info, 1);
        }
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_S))
	{
        if (((int)(info->player.pos.y + info->player.dir.y * info->frame.movment_speed) >=0
            && (int)(info->player.pos.x + info->player.dir.x * info->frame.movment_speed) >=0)
            && ((int)(info->player.pos.y + info->player.dir.y * info->frame.movment_speed) < info->map_y)
            && (int)(info->player.pos.x + info->player.dir.x * info->frame.movment_speed) < info->map_x)
        {
            move_vertical(info, -1);
        }
	}
    if (mlx_is_key_down(info->mlx, MLX_KEY_D))
    {
          if (((int)(info->player.pos.y + info->player.plane.y * info->frame.movment_speed) >= 0
            && (int)(info->player.pos.x + info->player.plane.x * info->frame.movment_speed) >= 0)
            && ((int)(info->player.pos.y + info->player.plane.y * info->frame.movment_speed) < info->map_y)
            && (int)(info->player.pos.x + info->player.plane.x * info->frame.movment_speed) < info->map_x)
        {
            if (info->map[(int)(info->player.pos.y + info->player.plane.y * info->frame.movment_speed)][(int)info->player.pos.x] == '0')
            {
                info->player.pos.y += info->player.plane.y * info->frame.movment_speed;
            }
            if (info->map[(int)info->player.pos.y][(int)(info->player.pos.x + info->player.plane.x * info->frame.movment_speed)] == '0')
            {
                info->player.pos.x += info->player.plane.x * info->frame.movment_speed;
            }
        }
    }
    if (mlx_is_key_down(info->mlx, MLX_KEY_A))
    {
         if (((int)(info->player.pos.y - info->player.plane.y * info->frame.movment_speed) >= 0
            && (int)(info->player.pos.x - info->player.plane.x * info->frame.movment_speed) >= 0)
            && ((int)(info->player.pos.y - info->player.plane.y * info->frame.movment_speed) < info->map_y)
            && (int)(info->player.pos.x - info->player.plane.x * info->frame.movment_speed) < info->map_x)
        {
            if (info->map[(int)(info->player.pos.y - info->player.plane.y * info->frame.movment_speed)][(int)info->player.pos.x] == '0')
            {
                info->player.pos.y -= info->player.plane.y * info->frame.movment_speed;
            }
            if (info->map[(int)info->player.pos.y][(int)(info->player.pos.x - info->player.plane.x * info->frame.movment_speed)] == '0')
            {
                info->player.pos.x -= info->player.plane.x * info->frame.movment_speed;
            }
        }
    }
    //rotation
    // printf("plane:\nx:\t%d\ny\t:%d\ndirection:\nx:\t%d\ny:\t%d\n", (int)info->player.plane.x, (int)info->player.plane.y, (int)info->player.dir.x, (int)info->player.dir.y);
    double old_plane_x = info->player.plane.x;
    double old_dir_x = info->player.dir.x;
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
	{
        //both camera directions must be rotated
        // printf("rotation speed:\t%f\nplayer dir\nx:\t%f\ny:\t%f\n", info->frame.rotation_speed, info->player.dir.x, info->player.dir.y);
        info->player.dir.x = info->player.dir.x * cos(info->frame.rotation_speed) - info->player.dir.y * sin(info->frame.rotation_speed);
        info->player.dir.y = old_dir_x * sin(info->frame.rotation_speed) + info->player.dir.y * cos(info->frame.rotation_speed);
        info->player.plane.x = info->player.plane.x * cos(info->frame.rotation_speed) - info->player.plane.y * sin(info->frame.rotation_speed);
        info->player.plane.y = old_plane_x * sin(info->frame.rotation_speed) + info->player.plane.y * cos(info->frame.rotation_speed);
	}   
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
	{
        // printf("rotation speed:\t%f\nplayer dir\nx:\t%f\ny:\t%f\n", info->frame.rotation_speed, info->player.dir.x, info->player.dir.y);
        info->player.dir.x = info->player.dir.x * cos(-info->frame.rotation_speed) - info->player.dir.y * sin(-info->frame.rotation_speed);
        info->player.dir.y = old_dir_x * sin(-info->frame.rotation_speed) + info->player.dir.y * cos(-info->frame.rotation_speed);
        info->player.plane.x = info->player.plane.x * cos(-info->frame.rotation_speed) - info->player.plane.y * sin(-info->frame.rotation_speed);
        info->player.plane.y = old_plane_x * sin(-info->frame.rotation_speed) + info->player.plane.y * cos(-info->frame.rotation_speed);
	}
    //das heisst ei tam move?move_player
    //da berechnen sie move udn rotation
    //da passiert glaube ich alles hier
    render_wrld(info);
}