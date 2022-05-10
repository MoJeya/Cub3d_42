
#include "cub3d.h"

void test_print(t_gen_info *info)
{
	int i;
	printf("PATH: %s\n", info->texture_SO_path);
	printf("PATH: %s\n", info->texture_NO_path);
	printf("PATH: %s\n", info->texture_WE_path);
	printf("PATH: %s\n", info->texture_EA_path);
	printf("F:\nred:%d\nyellow:%d\nblue:%d\n", info->floor.red, info->floor.yellow, info->floor.blue);
	printf("C:\nred:%d\nyellow:%d\nblue:%d\n", info->ceiling.red, info->ceiling.yellow, info->ceiling.blue);
	printf("MAP: \n");
	// printf("%s", info->map[info->map_height - 1]);
	
	i = 0;
	while(info->map[i] != NULL)
	{
	printf("%s", info->map[i]);
		i++;
	}
}

int main(int argc, char *argv[])
{
	t_gen_info info;
	if (init_data_info(&info, argv, argc))
	//1.1) was wenn keine spieler position angegeben ist
	//2.2)checken wir wirklich, dass der komplette rahmen aus 1en besteht?
	//4) NO(abc)/SO/... if fail, dann exiten
	//5) es darf auch nur ein mal N/S/W/E vorkommen oder ?
	{
		test_print(&info);
		create_window();
		//macht, dass die letzte Zeile nicht geprinted wird --- YYY?
	}
	// create_window();
	// system("leaks cube3d");
	return(0);
}