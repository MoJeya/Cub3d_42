
#include "cub3d.h"

// char    **shift_map(t_gen_info *info)
// {
//     char **tmp_map;
//     int x;
//     int x_tmp;
//     int y;

//     x = 0;
//     x_tmp = 0;
//     y = 0;
//     tmp_map = (char **)malloc(info->map_x, sizeof(char *));
//     if (!tmp_map)
//         return (NULL);
//     while (info->map[y])
//     {
//         x = 0;
//         tmp_map[y] = ft_calloc()
//         while (info->map[x][y] != '\0')
//         {
            
//         }
//     }
// }

void draw_lines(t_gen_info *info, int x)
{
    int i;

    i = 0;
    while (i < screenHeight)
	{
	    if (i >= info->raycast.draw_start && i <= info->raycast.draw_end)
	    {
		    mlx_put_pixel(info->m_img, x, i, 0x00000000);
		    if (info->side == 0)
			    mlx_put_pixel(info->m_img, x, info->raycast.draw_start++, 0xFFFFFFFF);
		    else
			    mlx_put_pixel(info->m_img, x, info->raycast.draw_start++, 0xAAFFFFFF);
	    }
	    else if (i < info->raycast.draw_start)
		    mlx_put_pixel(info->m_img, x, i, 0xDDAAFFFF);
	    else
		    mlx_put_pixel(info->m_img, x, i, 0x00000000);
	    i++;
	}
}

long time_stamp()
{
    struct timeval current_time;
    
    gettimeofday(&current_time, NULL);
    return (current_time.tv_usec/1000);

}


void    main_loop(t_gen_info *info)
{
    int x;
    int y;
    int map_pos_x; //which box of the map we're in
    int map_pos_y; //which box of the map we're in
    int screen_w;
    int screen_h;
  
    x = 0;
    y = 0;
    info->side = 0; //was a NS or a EW wall hit?
    info->frame.time = time_stamp();
    info->frame.old_time = 0;
    info->frame.frame_time = 0;
    info->frame.movment_speed = 0;
    info->frame.rotation_speed = 0;
    screen_w = screenWidth;
    screen_h = screenHeight;
// printf("Player pos x: %f\nplayer pos y: %f\n", info->player.pos.x, info->player.pos.y);
    while (x < screenWidth)
    {
        info->hit = 0; // was the a wall?
        info->raycast.camera_x = 2 * x / (double)screen_w - 1;
        info->raycast.dir.x = info->player.dir.x + info->player.plane.x * info->raycast.camera_x;
        info->raycast.dir.y = info->player.dir.y  + info->player.plane.y * info->raycast.camera_x;
        // printf("%d....\nraycast cam:\t%f\nraycast dir x:\t%f\nraycast dir y:\t%f\n",x, info->raycast.camera_x, info->raycast.dir.x, info->raycast.dir.y);
        map_pos_x = (int)info->player.pos.x;
        map_pos_y = (int)info->player.pos.y;

        if (info->raycast.dir.x == 0)
            info->raycast.delta_dist.x = 1e30;
        else
            info->raycast.delta_dist.x = fabs(1 / info->raycast.dir.x);
        if (info->raycast.dir.y == 0)
            info->raycast.delta_dist.y = 1e30;
        else
            info->raycast.delta_dist.y = fabs(1/ info->raycast.dir.y);
        // printf("raycast side\nx:\t%f\ny:\t%f\nraycast_delta\nx:\t%f\ny:\t%f\n",info->raycast.side_dist.x, info->raycast.side_dist.y, info->raycast.delta_dist.x, info->raycast.delta_dist.y);
        
        if (info->raycast.dir.x < 0)
        {
            info->player.step_x = -1;
            info->raycast.side_dist.x = (info->player.pos.x - map_pos_x) * info->raycast.delta_dist.x;
        }
        else
        {
            info->player.step_x = 1;
            info->raycast.side_dist.x = (map_pos_x + 1.0 - info->player.pos.x) * info->raycast.delta_dist.x;
        }
        if (info->raycast.dir.y < 0)
        {
            info->player.step_y = -1;
            info->raycast.side_dist.y = (info->player.pos.y - map_pos_y) * info->raycast.delta_dist.y;
        }
        else
        {
            info->player.step_y = 1;
            info->raycast.side_dist.y = (map_pos_y + 1.0 - info->player.pos.y) * info->raycast.delta_dist.y;
        }
        //DDA CALCUTALTION PERFORMED
        // printf("hit:\t%d\n", info->hit);
        while(info->hit == 0)
        {
            if (info->raycast.side_dist.x < info->raycast.side_dist.y)
            {
                info->raycast.side_dist.x += info->raycast.delta_dist.x;
                map_pos_x += info->player.step_x;
                info->side = 0;
            }
            else
            {
            // printf("side dist y:\t%f\n", info->raycast.side_dist.y);
               info->raycast.side_dist.y += info->raycast.delta_dist.y;
            // printf("side dist y:\t%f\n", info->raycast.side_dist.y);
               map_pos_y += info->player.step_y;
               info->side = 1; 
            }
            if (info->map[map_pos_y][map_pos_x] > '0')
            {
                // printf("map hit:\nx:\t%d\ny:\t%d\n", map_pos_x, map_pos_y);
                info->hit = 1;
            }
        }
        //calculated distance projected on the camera direction
        // printf("side:\t%d\n", info->side);
        // printf("\n");
        if (info->side == 0)
            info->player.prep_wall_dist = (info->raycast.side_dist.x - info->raycast.delta_dist.x);
        else
            info->player.prep_wall_dist = (info->raycast.side_dist.y - info->raycast.delta_dist.y);
        // printf("(side dist y - raycast delta dist y): %f - %f = %f\n", info->raycast.side_dist.y, info->raycast.delta_dist.y, info->player.prep_wall_dist);
        // printf("prepWallDist:\t%f\nsideDistX:\t%f\ndeltaDistX:\t%f\n",info->player.prep_wall_dist, info->raycast.side_dist.x, info->raycast.delta_dist.x);
        //line height calculation
        info->line_h = (int)(screen_h / info->player.prep_wall_dist);
        // printf("lineHEIGHT:\t%d\n", info->line_h);
        //calculate min and max pixel to fill current stripe
        info->raycast.draw_start = -info->line_h / 2 + screen_h / 2;
        if (info->raycast.draw_start < 0)
            info->raycast.draw_start = 0;
        info->raycast.draw_end = info->line_h / 2 + screen_h / 2;
        if (info->raycast.draw_end >= screen_h)
            info->raycast.draw_end = screen_h - 1;
        // printf("map[%d][%d]: %c\n", map_pos_x, map_pos_y, info->map[map_pos_x][map_pos_y]);
        draw_lines(info, x);
        //AUSLAGERN
        x++;
    }
    //should be put in to a new Image
    info->frame.old_time = info->frame.time;
    info->frame.time = time_stamp();
    // printf("time:\t%f\nold time:\t%f\n", info->frame.time, info->frame.old_time);
    info->frame.frame_time = (info->frame.time - info->frame.old_time) / 5.0;
    // printf("frame time: %f\n", info->frame.frame_time);
    info->frame.movment_speed = info->frame.frame_time * 0.10;
    // printf("movment speed:\t%f\n", info->frame.movment_speed);
    info->frame.rotation_speed = info->frame.frame_time * 0.10;
    // printf("calculations are finished!\n");
}

void player_movment(void *param)
{
	t_gen_info *info;

	info = param;

    printf("map:\t%c", info->map[(int)(info->player.pos.y + info->player.dir.y * info->frame.movment_speed)][(int)info->player.pos.x]);
    printf("\tplayer pos x:\t%f y\t%f\n", info->player.pos.x, info->player.pos.y);
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
    {
        mlx_delete_image(info->mlx, info->m_img);
		mlx_close_window(info->mlx);
    }
	if (mlx_is_key_down(info->mlx, MLX_KEY_W))
	{
        if (info->map[(int)(info->player.pos.y + info->player.dir.y * info->frame.movment_speed)][(int)info->player.pos.x] == '0')
        {
            info->player.pos.x += info->player.dir.x * info->frame.movment_speed;
        }
        if (info->map[(int)info->player.pos.y][(int)(info->player.pos.x + info->player.dir.x * info->frame.movment_speed)] == '0')
        {
            info->player.pos.y += info->player.dir.y * info->frame.movment_speed;
        }
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_S))
	{
        if (info->map[(int)(info->player.pos.y - info->player.dir.y * info->frame.movment_speed)][(int)info->player.pos.x] == '0')
            info->player.pos.y -= info->player.dir.y * info->frame.movment_speed;
        if (info->map[(int)info->player.pos.y][(int)(info->player.pos.x - info->player.dir.x * info->frame.movment_speed)] == '0')
            info->player.pos.x -= info->player.dir.x * info->frame.movment_speed;
	}
    //rotation
	if (mlx_is_key_down(info->mlx, MLX_KEY_A))
	{
        //both camera directions must be rotated
        // printf("rotation speed:\t%f\nplayer dir\nx:\t%f\ny:\t%f\n", info->frame.rotation_speed, info->player.dir.x, info->player.dir.y);
        double old_dir_x = info->player.dir.x;
        info->player.dir.x = info->player.dir.x * cos(info->frame.rotation_speed) - info->player.dir.y * sin(info->frame.rotation_speed);
        info->player.dir.y = old_dir_x * sin(info->frame.rotation_speed) + info->player.dir.y * cos(info->frame.rotation_speed);
        double old_plane_x = info->player.plane.x;
        info->player.plane.x = info->player.plane.x * cos(info->frame.rotation_speed) - info->player.plane.y * sin(info->frame.rotation_speed);
        info->player.plane.y = old_plane_x * sin(info->frame.rotation_speed) + info->player.plane.y * cos(info->frame.rotation_speed);
	}   
	if (mlx_is_key_down(info->mlx, MLX_KEY_D))
	{
        // printf("rotation speed:\t%f\nplayer dir\nx:\t%f\ny:\t%f\n", info->frame.rotation_speed, info->player.dir.x, info->player.dir.y);
        double old_dir_x = info->player.dir.x;
        info->player.dir.x = info->player.dir.x * cos(-info->frame.rotation_speed) - info->player.dir.y * sin(-info->frame.rotation_speed);
        info->player.dir.y = old_dir_x * sin(-info->frame.rotation_speed) + info->player.dir.y * cos(-info->frame.rotation_speed);
        double old_plane_x = info->player.plane.x;
        info->player.plane.x = info->player.plane.x * cos(-info->frame.rotation_speed) - info->player.plane.y * sin(-info->frame.rotation_speed);
        info->player.plane.y = old_plane_x * sin(-info->frame.rotation_speed) + info->player.plane.y * cos(-info->frame.rotation_speed);
	}
    main_loop(info);
}