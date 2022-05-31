
#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/*
void	get_textures(t_gen_info *info)
{
	int i;

	i = 0;

		info->xpm[0] = mlx_load_xpm42(info->texture_no_path);
		info->xpm[1] = mlx_load_xpm42(info->texture_so_path);
		info->xpm[2] = mlx_load_xpm42(info->texture_we_path);
		info->xpm[3] = mlx_load_xpm42(info->texture_ea_path);
	//muss hier noch irgendeine delete function hin??
}
*/

static double find_wall_x(t_gen_info *info)
{
    double wall_x;

    if (info->side == 0 || info->side == 1)
        wall_x = info->player.pos.y + info->player.prep_wall_dist * info->raycast.dir.y;
    else
        wall_x = info->player.pos.x + info->player.prep_wall_dist * info->raycast.dir.x;
    
    wall_x -= floor((wall_x));
    return (wall_x);
}
//hier fehlen dann noch die anderen 2 Wände

static int find_texture_x(t_gen_info *info, mlx_texture_t *texture)
{
    int tex_x;

    tex_x = (int)(find_wall_x(info) * (double)texture->width);
    if ((info->side == 0 && info->raycast.dir.x > 0)
	|| (info->side == 1 && info->raycast.dir.y < 0))
        tex_x = texture->width - tex_x - 1;
    return (tex_x);
}
//warum benutzt man nochmal statics???

void    insert_textures(t_gen_info *info, int x, int draw_start, int draw_end)
{
    mlx_texture_t   *texture;
    int             tex_x;
    int             tex_y;
    int             line_h;
    double          step;
    double          texture_pos;


    //je nachdem welche seite wir haben
    //und da wir immer nur auf einen vertikalen strich gucken
    //wird individuell die wand texture hier ausgesucht
    //dafur braucht es info->side
    texture = &info->xpm[info->side]->texture;

    tex_x = find_texture_x(info, texture);

    // line_h = (int)(screenHeight / info->player.prep_wall_dist);
	line_h = draw_end - draw_start;
    step = 1.0 * texture->height / line_h;
    texture_pos = (draw_start - screenHeight / 2 + line_h / 2) * step;
    while (draw_start < draw_end)
    {
        tex_y = (int)texture_pos & (texture->height - 1);
        texture_pos += step;
        if (draw_start >= 0 && draw_start <= screenHeight)
        {
            ft_memcpy(&info->m_img->pixels[(draw_start * info->m_img->width + x) * 4],
				&texture->pixels[(tex_y * texture->height + tex_x) * 4], 4);
            //vielleicht fehlen hier noch Klammern
        }
        draw_start++;
    }
    //die haben hier noch ne protection, falls des window halt geclosed wurde
    //vielleicht muss heir auch alles wieder x und y vertauscht werden
}

void draw_vertical_line(t_gen_info *info, int x)
{
    int i;

    i = 0;
    //heirvor kommt der texturize part
    //fur die calculation fehlen aber noch zwei seitenbestimmungen
    //bis jetzt haben wir nur 2 seitfarben, wir bracuhen aber 4 unterscheidungen
    insert_textures(info, x, info->raycast.draw_start, info->raycast.draw_end);

    while (i < screenHeight)
	{
//nur noch da bleibt dann e stehn fur boden und ceiling
	    if (i < info->raycast.draw_start)
		    mlx_put_pixel(info->m_img, x, i, create_trgb(info->ceiling.red, info->ceiling.yellow, info->ceiling.blue, 150));
	    if (i > info->raycast.draw_end)
		    mlx_put_pixel(info->m_img, x, i, create_trgb(info->floor.red, info->ceiling.yellow, info->floor.blue, 150));
		i++;
	}
}
//den Himmel malt unsers noch 
//aber der rest wird dann verschluckt
//todo 1) alle min werte einfügen
//todo 2) die beiden anderen walls einfügen
//todo 3) evtl müssen die x/y werte umgedreht werden


long time_stamp()
{
    struct timeval current_time;
    
    gettimeofday(&current_time, NULL);
    return (current_time.tv_usec/1000);
}


void    render_wrld(t_gen_info *info)
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
    //bis hier hin haben wir auch alles
    //jetzt kommt bei tam wie bei uns der WidthWhileLoop
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
        //tams set_loop
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
        //tams calc_step_and_side_dist
        //DDA CALCUTALTION PERFORMED
        // printf("hit:\t%d\n", info->hit);
        while(info->hit == 0)
        {
            if (info->raycast.side_dist.x < info->raycast.side_dist.y)
            {
                info->raycast.side_dist.x += info->raycast.delta_dist.x;
                map_pos_x += info->player.step_x;
                if (info->raycast.dir.x < 0)//stimmen die werte heir???
                    info->side = 0;//north
                else 
                    info->side = 1;//south
            }
            else
            {
            // printf("side dist y:\t%f\n", info->raycast.side_dist.y);
                info->raycast.side_dist.y += info->raycast.delta_dist.y;
            // printf("side dist y:\t%f\n", info->raycast.side_dist.y);
                map_pos_y += info->player.step_y;
                if (info->raycast.dir.y < 0)
                    info->side = 2; //west
                else
                    info->side = 3; //east
            }
            //check dda_case first part
            if (info->map[map_pos_y][map_pos_x] > '0')
            {
                // printf("map hit:\nx:\t%d\ny:\t%d\n", map_pos_x, map_pos_y);
                info->hit = 1;
            }
        }
        //calculated distance projected on the camera direction
        // printf("side:\t%d\n", info->side);
        // printf("\n");
        if (info->side == 0 || info->side == 1)
            info->player.prep_wall_dist = (info->raycast.side_dist.x - info->raycast.delta_dist.x);
        else
            info->player.prep_wall_dist = (info->raycast.side_dist.y - info->raycast.delta_dist.y);
        //TODO:tam und jakob haben hier noch zwei weitere wall unterscheidungen west east
        //check
        // printf("(side dist y - raycast delta dist y): %f - %f = %f\n", info->raycast.side_dist.y, info->raycast.delta_dist.y, info->player.prep_wall_dist);
        // printf("prepWallDist:\t%f\nsideDistX:\t%f\ndeltaDistX:\t%f\n",info->player.prep_wall_dist, info->raycast.side_dist.x, info->raycast.delta_dist.x);
        //line height calculation
        info->line_h = (int)(screen_h / info->player.prep_wall_dist);
        // printf("lineHEIGHT:\t%d\n", info->line_h);
        //calculate min and max pixel to fill current stripe
        info->raycast.draw_start = -info->line_h / 2 + screen_h / 2;
        // if (info->raycast.draw_start < 0)
            // info->raycast.draw_start = 0;
        info->raycast.draw_end = info->line_h / 2 + screen_h / 2;
        if (info->raycast.draw_end >= screen_h)
            info->raycast.draw_end = screen_h - 1;
        //des haben wir auch
        // printf("map[%d][%d]: %c\n", map_pos_x, map_pos_y, info->map[map_pos_x][map_pos_y]);
        draw_vertical_line(info, x);
        //AUSLAGERN
        x++;
    }
    //should be put in to a new Image
    info->frame.old_time = info->frame.time;
    info->frame.time = time_stamp();
    // printf("time:\t%f\nold time:\t%f\n", info->frame.time, info->frame.old_time);
    info->frame.frame_time = (info->frame.time - info->frame.old_time) / 10.0;
    // printf("frame time: %f\n", info->frame.frame_time);
    info->frame.movment_speed = info->frame.frame_time * 0.10;
    // printf("movment speed:\t%f\n", info->frame.movment_speed);
    info->frame.rotation_speed = info->frame.frame_time * 0.10;
    // printf("calculations are finished!\n");
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
            if (info->map[(int)(info->player.pos.y + info->player.dir.y * info->frame.movment_speed)][(int)info->player.pos.x] == '0')
            {
                info->player.pos.y += info->player.dir.y * info->frame.movment_speed;
            }
            if (info->map[(int)info->player.pos.y][(int)(info->player.pos.x + info->player.dir.x * info->frame.movment_speed)] == '0')
            {
                info->player.pos.x += info->player.dir.x * info->frame.movment_speed;
            }
        }
        // else
        // {
        //     printf("player pos:\n\tx:\t%f\n\ty:\t%f\n", info->player.pos.x, info->player.pos.y);
        // }
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_S))
	{
        if (((int)(info->player.pos.y + info->player.dir.y * info->frame.movment_speed) >=0
            && (int)(info->player.pos.x + info->player.dir.x * info->frame.movment_speed) >=0)
            && ((int)(info->player.pos.y + info->player.dir.y * info->frame.movment_speed) < info->map_y)
            && (int)(info->player.pos.x + info->player.dir.x * info->frame.movment_speed) < info->map_x)
        {
            if (info->map[(int)(info->player.pos.y - info->player.dir.y * info->frame.movment_speed)][(int)info->player.pos.x] == '0')
            {
                info->player.pos.y -= info->player.dir.y * info->frame.movment_speed;
            }
            if (info->map[(int)info->player.pos.y][(int)(info->player.pos.x - info->player.dir.x * info->frame.movment_speed)] == '0')
            {
                info->player.pos.x -= info->player.dir.x * info->frame.movment_speed;
            }
        }
        // else
        // {
        //     printf("player pos:\n\tx:\t%f\n\ty:\t%f\n", info->player.pos.x, info->player.pos.y);    
        // }
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
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
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
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
	{
        // printf("rotation speed:\t%f\nplayer dir\nx:\t%f\ny:\t%f\n", info->frame.rotation_speed, info->player.dir.x, info->player.dir.y);
        double old_dir_x = info->player.dir.x;
        info->player.dir.x = info->player.dir.x * cos(-info->frame.rotation_speed) - info->player.dir.y * sin(-info->frame.rotation_speed);
        info->player.dir.y = old_dir_x * sin(-info->frame.rotation_speed) + info->player.dir.y * cos(-info->frame.rotation_speed);
        double old_plane_x = info->player.plane.x;
        info->player.plane.x = info->player.plane.x * cos(-info->frame.rotation_speed) - info->player.plane.y * sin(-info->frame.rotation_speed);
        info->player.plane.y = old_plane_x * sin(-info->frame.rotation_speed) + info->player.plane.y * cos(-info->frame.rotation_speed);
	}
    //das heisst ei tam move?move_player
    //da berechnen sie move udn rotation
    //da passiert glaube ich alles hier
    render_wrld(info);
}