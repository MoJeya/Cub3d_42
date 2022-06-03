
#include "../cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

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


static int find_texture_x(t_gen_info *info, mlx_texture_t *texture)
{
    int tex_x;

    tex_x = (int)(find_wall_x(info) * (double)texture->width);
    if ((info->side == 0 && info->raycast.dir.x > 0)
	|| (info->side == 1 && info->raycast.dir.y < 0))
        tex_x = texture->width - tex_x - 1;
    return (tex_x);
}

void    insert_textures(t_gen_info *info, int x, int draw_start, int draw_end)
{
    mlx_texture_t   *texture;
    int             tex_x;
    int             tex_y;
    int             line_h;
    double          step;
    double          texture_pos;

    texture = &info->xpm[info->side]->texture;
    tex_x = find_texture_x(info, texture);
	line_h = draw_end - draw_start;
    step = 2.0 * texture->height / line_h;
    texture_pos = (draw_start - screenHeight / 2 + line_h / 2) * step;
    while (draw_start < draw_end)
    {
        tex_y = (int)texture_pos & (texture->height - 1);
        texture_pos += step;
        if (draw_start >= 0 && draw_start <= screenHeight)
        {
            ft_memcpy(&info->m_img->pixels[(draw_start * info->m_img->width + x) * 4],
				&texture->pixels[(tex_y * texture->height + tex_x) * 4], 4);
        }
        draw_start++;
    }
}

void draw_vertical_line(t_gen_info *info, int x)
{
    int i;

    i = 0;
    insert_textures(info, x, info->raycast.draw_start, info->raycast.draw_end);
    while (i < screenHeight)
	{
	    if (i < info->raycast.draw_start)
		    mlx_put_pixel(info->m_img, x, i, create_trgb(info->ceiling.red, info->ceiling.yellow, info->ceiling.blue, 150));
	    if (i > info->raycast.draw_end)
		    mlx_put_pixel(info->m_img, x, i, create_trgb(info->floor.red, info->ceiling.yellow, info->floor.blue, 150));
		i++;
	}
}

void    set_step(t_gen_info *info, int map_pos_x, int map_pos_y)
{

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
}

void dda_calc(t_gen_info *info, int map_pos_x, int map_pos_y)
{
    while (info->hit == 0)
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
            info->raycast.side_dist.y += info->raycast.delta_dist.y;
            map_pos_y += info->player.step_y;
            if (info->raycast.dir.y < 0)
                info->side = 2; //west
            else
                info->side = 3; //east
        }
        if (info->map[map_pos_y][map_pos_x] > '0')
        {
            // printf("\nplayer pos:\n\tx:\t%f\n\ty:\t%f\nmap_pos:\n\tx:\t%d\n\ty:\t%d\n", info->player.pos.x, info->player.pos.y, map_pos_x, map_pos_y);
            info->hit = 1;
        }
    }
}

void    render_wrld(void *param)
{

    t_gen_info *info;

    info = param;
    int x;
    int y;
    int map_pos_x; //which box of the map we're in
    int map_pos_y; //which box of the map we're in
    int screen_w;
    int screen_h;
  
    x = 0;
    y = 0;
    info->side = 0; //was a NS or a EW wall hit?
    info->frame.movment_speed = 0.05;
    info->frame.rotation_speed = 0.05;
    screen_w = screenWidth;
    screen_h = screenHeight;
// printf("plane: x{%f}\tt{%f}\n", info->player.plane.x, info->player.plane.y);
    while (x < screenWidth)
    {
        info->hit = 0; // was the a wall?
        info->player.step_x = 1;
        info->raycast.camera_x = (double)(2 * x) / (double)screen_w - 1;
        info->raycast.dir.x = info->player.dir.x + (info->player.plane.x * info->raycast.camera_x);
        info->raycast.dir.y = info->player.dir.y  + (info->player.plane.y * info->raycast.camera_x);
    // printf("raycast direction:\n{x}\t%f\n{y}\t%f", info->raycast.dir.x, info->raycast.dir.y);
        map_pos_x = (int)info->player.pos.x;
        map_pos_y = (int)info->player.pos.y;
        info->raycast.side_dist.x = (map_pos_x + 1.0 - info->player.pos.x) * info->raycast.delta_dist.x;
        if (info->raycast.dir.x == 0)
            info->raycast.delta_dist.x = INFINITY;
        else
            info->raycast.delta_dist.x = fabs(1 / info->raycast.dir.x);
        if (info->raycast.dir.y == 0)
            info->raycast.delta_dist.y = INFINITY;
        else
            info->raycast.delta_dist.y = fabs(1/ info->raycast.dir.y);
        set_step(info, map_pos_x, map_pos_y);
        dda_calc(info, map_pos_x, map_pos_y);
        if (info->side == 0 || info->side == 1)
            info->player.prep_wall_dist = (info->raycast.side_dist.x - info->raycast.delta_dist.x);
        else if (info->side == 2 || info->side == 3)
            info->player.prep_wall_dist = (info->raycast.side_dist.y - info->raycast.delta_dist.y);
        info->line_h = (int)(screen_h / info->player.prep_wall_dist);
        info->raycast.draw_start = -info->line_h / 2 + screen_h / 2;
        info->raycast.draw_end = info->line_h / 2 + screen_h / 2;
        if (info->raycast.draw_end >= screen_h)
            info->raycast.draw_end = screen_h - 1;
        draw_vertical_line(info, x);
        x++;
    }
    // info->frame.movment_speed = 0.05;
    // info->frame.rotation_speed = 0.05;
    draw_minimap(info);
    player_movment(info, map_pos_x, map_pos_y);
}



 