#include "../cub3d.h"

void draw_minimap(t_gen_info *info)
{
    // int mini_map_x = info->map_x * 16;
    // int mini_map_y = info->map_y * 16;
    int x;
    int y;
    int x_tile;
    int y_tile;

    x = -1;
    y = 0;
    x_tile = 0;
    y_tile = 0;
    while (y < info->map_y)
    {
        x = 0;
        x_tile = 0;
        while (x < info->map_x)
        {
            if (info->map[y][x] == '1')
                mlx_draw_texture(info->m_img, info->m_wall, x_tile, y_tile);
            if (info->map[y][x] == '0')
                mlx_draw_texture(info->m_img, info->back_g, x_tile, y_tile);
            if (info->map[y][x] == 'N')
                mlx_draw_texture(info->m_img, info->player_img, x_tile, y_tile);
            x_tile = x * TILES_W;
            x++;
        }
        y_tile = y * TILES_H;
        y++;
    }
}