
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
    info->side = 0; //was a NS or a EW wall hit?
    screen_w = screenWidth;
    screen_h = screenHeight;
// printf("Player pos x: %f\nplayer pos y: %f\n", info->player.pos.x, info->player.pos.y);
    while (x < screenWidth)
    {
        info->hit = 0; // was the a wall?
        info->raycast.camera_x = 2 * x / (double)screen_w - 1;
        info->raycast.dir.x = info->player.dir.x + info->player.plane.x * info->raycast.camera_x;
        info->raycast.dir.y = info->player.dir.y  + info->player.plane.y * info->raycast.camera_x;
        printf("%d....\nraycast cam:\t%f\nraycast dir x:\t%f\nraycast dir y:\t%f\n",x, info->raycast.camera_x, info->raycast.dir.x, info->raycast.dir.y);
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
        printf("hit:\t%d\n", info->hit);
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
                printf("map:\nx:\t%d\ny:\t%d\n", map_pos_x, map_pos_y);
                info->hit = 1;
            }
        }
        //calculated distance projected on the camera direction
        printf("side:\t%d\n", info->side);
        printf("\n");
        if (info->side == 0)
        {
     // printf("first option side == 0\n");
            info->player.prep_wall_dist = (info->raycast.side_dist.x - info->raycast.delta_dist.x);
        }
        else
        {
            info->player.prep_wall_dist = (info->raycast.side_dist.y - info->raycast.delta_dist.y);
        // printf("(side dist y - raycast delta dist y): %f - %f = %f\n", info->raycast.side_dist.y, info->raycast.delta_dist.y, info->player.prep_wall_dist);
        }
        // printf("prepWallDist:\t%f\nsideDistX:\t%f\ndeltaDistX:\t%f\n",info->player.prep_wall_dist, info->raycast.side_dist.x, info->raycast.delta_dist.x);
        //line height calculation
        info->line_h = (int)(screen_h / info->player.prep_wall_dist);
        printf("lineHEIGHT:\t%d\n", info->line_h);
        //calculate min and max pixel to fill current stripe
        int draw_start = -info->line_h / 2 + screen_h / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = info->line_h / 2 + screen_h / 2;
        if (draw_end >= screen_h)
            draw_end = screen_h - 1;
        // int color = 0xFFFFFFFF;
        // printf("map[%d][%d]: %c\n", map_pos_x, map_pos_y, info->map[map_pos_x][map_pos_y]);
        int i = 0;
	    while (i < screenHeight)
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
