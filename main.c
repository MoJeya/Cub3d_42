
#include "cub3d.h"

void test_print(t_gen_info *info)
{
	int	i;
	printf("PATH: %s\n", info->texture_so_path);
	printf("PATH: %s\n", info->texture_no_path);
	printf("PATH: %s\n", info->texture_we_path);
	printf("PATH: %s\n", info->texture_ea_path);
	printf("F:\nred:%d\nyellow:%d\nblue:%d\n", info->floor.red, info->floor.yellow, info->floor.blue);
	printf("C:\nred:%d\nyellow:%d\nblue:%d\n", info->ceiling.red, info->ceiling.yellow, info->ceiling.blue);
	printf("MAP: \n");
	i = 0;
	while (info->map[i] != NULL)
	{
		printf("%s\n", info->map[i]);
		i++;
	}
	// printf("player is looking: %c\n", info->player.looking);
	printf("Player pos x: %f\nplayer pos y: %f\n", info->player.pos.x, info->player.pos.y);
	printf("\n");
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
	info->side = 0; //was a NS or a EW wall hit?
    info->frame.old_time = 0;
    info->frame.frame_time = 0;
    info->frame.movment_speed = 0;
    info->frame.rotation_speed = 0;
}

void	init_raycast_info(t_gen_info *info)
{
	// printf("player directio: %c", info->player.looking);
	if (info->player.looking == 'W')
	{
		info->player.dir.x = -1 * cos(0) - 0 * sin(0);
    	info->player.dir.y = -1 * sin(0) + 0 * cos(0);
    	info->player.plane.x = 0 * cos(0) - 0.66 * sin(0);
    	info->player.plane.y = 0 * sin(0) + 0.66 * cos(0);
	}
	else if (info->player.looking == 'S')
	{
		info->player.dir.x = -1 * cos(180) - 0 * sin(180);
    	info->player.dir.y = -1 * sin(180) + 0 * cos(180);
    	info->player.plane.x = 0 * cos(180) - 0.66 * sin(180);
    	info->player.plane.y = 0 * sin(180) + 0.66 * cos(180);
	}
	else if (info->player.looking == 'N')
	{
		info->player.dir.x = -1 * cos(90) - 0 * sin(90);
    	info->player.dir.y = -1 * sin(90) + 0 * cos(90);
    	info->player.plane.x = 0 * cos(90) - 0.66 * sin(90);
    	info->player.plane.y = 0 * sin(90) + 0.66 * cos(90);
	}
	else if (info->player.looking == 'E')
	{
		info->player.dir.x = -1 * -cos(0) - 0 * -sin(0);
    	info->player.dir.y = -1 * -sin(0) + 0 * -cos(0);
    	info->player.plane.x = 0 * -cos(0) - 0.66 * -sin(0);
    	info->player.plane.y = 0 * -sin(0) + 0.66 * -cos(0);
	}
	// info->player.dir.x = -1;
	// info->player.dir.y = 0;
	// info->player.plane.x = 0;
	// info->player.plane.y = 0.66;
    info->player.step_x = 0;
    info->player.step_y = 0;
    info->raycast.camera_x = 0;
}

int	main(int argc, char *argv[])
{
	t_gen_info info;

	init_genaral_info(&info);
	// printf("Hex color: 125 155 200 in decimal: x0%X%X%X%X\n", 125, 155, 200, 255);
	if (init_data_info(&info, argv, argc))
	//1.1) was wenn keine spieler position angegeben ist
	{
		init_raycast_info(&info);
		// test_print(&info);
		create_window(&info);
	}
	// create_window();
	// system("leaks cube3d");
	return(0);
}
