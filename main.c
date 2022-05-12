
#include "cub3d.h"

void test_print(t_gen_info *info)
{
	int	i;
	printf("PATH: %s\n", info->texture_SO_path);
	printf("PATH: %s\n", info->texture_NO_path);
	printf("PATH: %s\n", info->texture_WE_path);
	printf("PATH: %s\n", info->texture_EA_path);
	printf("F:\nred:%d\nyellow:%d\nblue:%d\n", info->floor.red, info->floor.yellow, info->floor.blue);
	printf("C:\nred:%d\nyellow:%d\nblue:%d\n", info->ceiling.red, info->ceiling.yellow, info->ceiling.blue);
	printf("MAP: \n");
	// printf("%s", info->map[info->map_height - 1]);
	i = 0;
	while (info->map[i] != NULL)
	{
		printf("%s", info->map[i]);
		i++;
	}
}

void	init_genaral_info(t_gen_info *info)
{
	printf("here2\n");
	info->map_x = 0;
	info->map_y = 0;
	info->map_height = 0;
	info->map_widht = 0;
	info->ceiling.set = false;
	info->ceiling.red = 0;
	info->ceiling.yellow = 0;
	info->ceiling.blue = 0;
	info->floor.set = false;
	info->floor.red = 0;
	info->floor.yellow = 0;
	info->floor.blue = 0;
	info->path = NULL;
}

int	main(int argc, char *argv[])
{
	t_gen_info info;

	init_genaral_info(&info);
	if (init_data_info(&info, argv, argc))
	//1.1) was wenn keine spieler position angegeben ist
	{
		printf("here main\n");
		test_print(&info);
		create_window();
	}
	// create_window();
	// system("leaks cube3d");
	return(0);
}