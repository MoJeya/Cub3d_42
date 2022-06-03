#include "../cub3d.h"

void draw_minimap(t_gen_info *info)
{
    int x;//tatsachliche position im array
    int y;
    int x_tile;//pixel grösse für die anordnung im window
    int y_tile;

    x = 0;
    y = 0;
    // x_tile = 0;
    y_tile = 0;
    while (y < info->map_y)
    {
        x = 0;
        x_tile = screenWidth - (info->map_x - 1) * TILES_W;
        while (x < info->map_x)
        {
            if (info->map[y][x] == '1')
                mlx_draw_texture(info->m_img, info->m_wall, x_tile, y_tile);
            if (info->map[y][x] == '0')
                mlx_draw_texture(info->m_img, info->back_g, x_tile, y_tile);

			x_tile += TILES_W;
            x++;
        }
		y_tile += TILES_H;
        y++;
    }
}
//was aber beim ersten Mal reinkommen???

void    minimap_movement(t_gen_info *info)
{
    int mini_x;
    int mini_y;

    mini_x = ((info->player.pos.x / info->map_x) * (info->map_x * TILES_W)//player.pos.3d / 33
                + screenWidth - (info->map_x * TILES_W)) - TILES_W / 2;
    mini_y = ((info->player.pos.y / info->map_y) * (info->map_y * TILES_H)
                - TILES_H / 2);
    if (info->map[(int)info->player.map_pos_y][(int)(info->player.map_pos_x - 0.5)] == '1')
        mini_x = (mini_x - (mini_x % 8)) + 8;
    if (info->map[(int)info->player.map_pos_y][(int)(info->player.map_pos_x + 0.5)] == '1')
        mini_x = (mini_x - (mini_x % 8));
    if (info->map[(int)(info->player.map_pos_y - 0.5)][(int)info->player.map_pos_x] == '1')
        mini_y = (mini_y - (mini_y % 8)) + 8;
    if (info->map[(int)(info->player.map_pos_y + 0.5)][(int)info->player.map_pos_x] == '1')
        mini_y = (mini_y - (mini_y % 8));
    mlx_draw_texture(info->m_img, info->player_img, mini_x, mini_y);
    //function Aufruf
}