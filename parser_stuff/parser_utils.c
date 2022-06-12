
#include "../cub3d.h"

void	set_no_so(t_gen_info *info, char **str, int i)
{
	// printf("in 1 i: %d\nstr:\t%s\n", i, str[i]);
	if (strcomp(str[i], "NO "))
	{
		if (store_texture("NO ", str[i], &info->texture_no_path))
		{
			info->success++;
			info->check[0] = true;
		}
	}
	if (strcomp(str[i], "SO "))
	{
		if (store_texture("SO ", str[i], &info->texture_so_path))
		{
			info->success++;
			info->check[1] = true;
		}
	}
}

void	set_we_ea(t_gen_info *info, char **str, int i)
{
	// printf("in 2 i: %d\nstr:\t%s\n", i, str[i]);
	if (strcomp(str[i], "WE "))
	{
		if (store_texture("WE ", str[i], &info->texture_we_path))
		{
			info->success++;
			info->check[2] = true;
		}
	}
	if (strcomp(str[i], "EA "))
	{
		if (store_texture("EA ", str[i], &info->texture_ea_path))
		{
			printf("%s\n", str[i]);
			info->success++;
			info->check[3] = true;
		}
	}
}