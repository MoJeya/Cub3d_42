
#include "../cub3d.h"


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
    texture_pos = (draw_start - SCREEN_H / 2 + line_h / 2) * step;
    while (draw_start < draw_end)
    {
        tex_y = (int)texture_pos & (texture->height - 1);
        texture_pos += step;
        if (draw_start >= 0 && draw_start <= SCREEN_H)
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
    while (i < SCREEN_H)
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
    int map_pos_x;
    int map_pos_y;
  
    x = 0;
    y = 0;
    info->side = 0;
    info->frame.movment_speed = 0.05;
    info->frame.rotation_speed = 0.05;
    while (x < SCREEN_W)
    {
        set_startval(x, info);
        map_pos_x = (int)info->player.pos.x;
        map_pos_y = (int)info->player.pos.y;
        info->raycast.side_dist.x = (map_pos_x + 1.0 - info->player.pos.x) * info->raycast.delta_dist.x;
        set_delta_dist(info);
        set_step(info, map_pos_x, map_pos_y);
        dda_calc(info, map_pos_x, map_pos_y);
        calc_perp_walldist(info);
        set_line_height(info);
        draw_vertical_line(info, x);
        x++;
    }
    player_movment(info);
    draw_minimap(info);
    minimap_movement(info);
}



 