
#include "cub3d.h"

void	get_textures(t_gen_info *info)
{
	int i;

	i = 0;

	info->xpm[0] = mlx_load_xpm42(info->texture_no_path);
	info->xpm[1] = mlx_load_xpm42(info->texture_so_path);
	info->xpm[2] = mlx_load_xpm42(info->texture_we_path);
	info->xpm[3] = mlx_load_xpm42(info->texture_ea_path);
	info->m_wall = mlx_load_png("./minimap/img/dungeon.png");
	info->player_img = mlx_load_png("./minimap/img/person.png");
	info->back_g = mlx_load_png("./minimap/img/playground.png");
	//muss hier noch irgendeine delete function hin??
	//nein sonst free fehler
}

void	init_genaral_info(t_gen_info *info)
{
	info->map_x = 0;
	info->map_y = 0;
	info->win_x = 0;
	info->win_y = 0;
	info->ceiling.set = false;
	info->ceiling.red = 0;
	info->ceiling.yellow = 0;
	info->ceiling.blue = 0;
	info->floor.set = false;
	info->floor.red = 0;
	info->floor.yellow = 0;
	info->floor.blue = 0;
	info->path = NULL;
	info->side = 0;
	info->player.step_x = 0;
    info->player.step_y = 0;
    info->raycast.camera_x = 0;
    info->frame.old_time = 0;
    info->frame.frame_time = 0;
    info->frame.movment_speed = 0;
    info->frame.rotation_speed = 0;
}

void	init_raycast_info(t_gen_info *info)
{
	info->player.dir.x = 0;
	info->player.dir.y = -1;
	info->player.plane.x = -0.66;
	info->player.plane.y = 0;
	if (info->player.looking == 'W')
	{
		info->player.dir.x = 1;
		info->player.dir.y = 0;
		info->player.plane.y = -0.66;
		info->player.plane.x = 0;
	}
	else if (info->player.looking == 'S')
	{
		info->player.dir.x = 0;
		info->player.dir.y = 1;
		info->player.plane.x = 0.66;
		info->player.plane.y = 0;	
	}
	else if (info->player.looking == 'E')
	{
		info->player.dir.x = -1;
		info->player.dir.y = 0;
		info->player.plane.x = 0;
		info->player.plane.y = 0.66;
	}

}

int	main(int argc, char *argv[])
{
	t_gen_info info;

	init_genaral_info(&info);
	if (init_data_info(&info, argv, argc))
	{
		get_textures(&info);
		init_raycast_info(&info);
		create_window(&info);
	}
	error_free_exit(NULL, &info, INFO_MAP);
	// create_window();
	// system("leaks cube3d");
	return(0);
}
