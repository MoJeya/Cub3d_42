#include "../cub3d.h"

int	map_parse_condition(t_gen_info *info, int i)
{
	if (info->info_string[i][0] == ' '
		|| info->info_string[i][0] == '0'
		|| info->info_string[i][0] == '1')
	{
		return (1);
	}
	return (0);
}
//hier könte man die 0 gleich weg lassen
//da am Anfnag ja nur leer oder 1 sein darf?

int	parse_color_settings(char *str, t_gen_info *info)
{
	if (!ft_strncmp(str, "F ", ft_strlen("F ")))
	{
		if (!split_values(str, info))
			return (0);
		return (1);
	}
	else if (!ft_strncmp(str, "C ", ft_strlen("C ")))
	{
		if (!split_values(str, info))
			return (0);
		return (1);
	}
	return (1);
}

int	init_text_struct(char *str, t_gen_info *info)
{
	if (strcomp(str, "NO ") == 1)
	{
		info->texture_NO_path = ft_strdup(str + ft_strlen("NO "));
		if (!info->texture_NO_path)
			return (1);
	}
	else if (strcomp(str, "SO "))
	{
		info->texture_SO_path = ft_strdup(str + ft_strlen("SO "));
		if (!info->texture_SO_path)
			return (1);
	}
	else if (strcomp(str, "WE "))
	{
		info->texture_WE_path = ft_strdup(str + ft_strlen("WE "));
		if (!info->texture_WE_path)
			return (1);
	}
	else if (strcomp(str, "EA "))
	{
		info->texture_EA_path = ft_strdup(str + ft_strlen("EA "));
		if (!info->texture_EA_path)
			return (1);
	}
	return (0);
}

int	set_values_to_map(t_gen_info *info, char **str, int *y)
{
	int	j;
	int	x;

	while (str[(*y)] != NULL)
	{
		j = 0;
		x = 0;
		info->map[(*y)] = my_calloc(info->map_x, sizeof(char), info, INFO_MAP);
		while (str[(*y)][j] != 0 && str[(*y)][j] != 10 && j < info->map_x)
		{
			ft_memset(&info->map[(*y)][x], str[(*y)][j], 1);
			j++;
			x++;
		}
		while (x < (info->map_x - 1))
		{
			info->map[(*y)][x] = '1';
			x++;
		}
		info->map[(*y)][x] = '\0';
		(*y)++;
	}
	return ((*y));
}

int	init_map(t_gen_info *info, char **str)
{
	int	y;

	y = 0;
	info->map = my_calloc(info->map_y + 1, sizeof(char *), info, INFO_MAP);
	y = set_values_to_map(info, str, &y);
	info->map[y] = NULL;
	return (1);
}
