
#include "cub3d.h"

void    main_loop(t_gen_info *info, mlx_image_t *map)
{
    info->player.dir.x = -1;
    info->player.dir.y = 0;
    info->player.plane.x = 0;
    info->player.plane.y = 0.66;
    info->player.step_x = 0;
    info->player.step_y = 0;
    info->raycast.camera_x = 0;
  

    int x;
    int y;
    int map_pos_x; //which box of the map we're in
    int map_pos_y; //which box of the map we're in
    int screen_w;
    int screen_h;
  
    x = 0;
    y = 0;
    info->hit = 0; // was the a wall?
    info->side = 0; //was a NS or a EW wall hit?
    screen_w = SCREEN_WIDHT;
    screen_h = SCREEN_HEIGHT;
    while (x < SCREEN_WIDHT)
    {
        info->raycast.camera_x = 2 * x / (double)screen_w - 1;
        info->raycast.dir.x = info->player.dir.x + info->player.plane.x * info->raycast.camera_x;
        info->raycast.dir.y = info->player.dir.y  + info->player.plane.y * info->raycast.camera_x;
printf("raycast cam:\t%f\nraycast dir x:\t%f\nraycast dir y:\t%f\n", info->raycast.camera_x, info->raycast.dir.x, info->raycast.dir.y);
        map_pos_x = (int)info->player.pos.y;
        map_pos_y = (int)info->player.pos.x;

        if (info->raycast.dir.x == 0)
            info->raycast.delta_dist.x = 1e30;
        else
            info->raycast.delta_dist.x = fabs(1 / info->raycast.dir.x);
        if (info->raycast.dir.y == 0)
            info->raycast.delta_dist.y = 1e30;
        else
            info->raycast.delta_dist.y = fabs(1/ info->raycast.dir.y);
printf("raycast_delta\nx:\t%f\ny:\t%f\n", info->raycast.delta_dist.x, info->raycast.delta_dist.y);
        
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
               info->raycast.side_dist.y += info->raycast.delta_dist.y;
               map_pos_y += info->player.step_y;
               info->side = 1; 
            }
            if (info->map[map_pos_x][map_pos_y] > 0)
                info->hit = 1;
        }
        //calculated distance projected on the camera direction
        if (info->side == 0)
            info->player.prep_wall_dist = (info->raycast.side_dist.x - info->raycast.delta_dist.x);
        else
            info->player.prep_wall_dist = (info->raycast.side_dist.y - info->raycast.delta_dist.y);

        //line height calculation
        info->line_h = (int)(screen_w / info->player.prep_wall_dist);
    printf("lineHEIGHT:\t%d\n", info->line_h);
        //calculate min and max pixel to fill current stripe
        int draw_start = -info->line_h / 2 * screen_h / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = info->line_h / 2 + screen_h / 2;
        if (draw_end >= screen_h)
            draw_end = screen_h - 1;
        // int color = 0xFFFFFFFF;
printf("map[%d][%d]: %c\n", map_pos_x, map_pos_y, info->map[map_pos_x][map_pos_y]);
        int i = 0;
	    while (i < SCREEN_HEIGHT)
	    {
		    if (i >= draw_start && i <= draw_end)
		    {
			    mlx_put_pixel(map, x, i, 0x00000000);
			    if (info->side == 0)
				    mlx_put_pixel(map, x, draw_start++, 0xFFFFFFFF);
			    else
				    mlx_put_pixel(map, x, draw_start++, 0xAAFFFFFF);

		    }
		    else if (i < draw_start)
			    mlx_put_pixel(map, x, i, 0xDDAAFFFF);
		    else
			    mlx_put_pixel(map, x, i, 0x00000000);
		    i++;
	    }
        x++;
    }


}
