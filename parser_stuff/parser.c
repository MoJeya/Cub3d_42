
#include "../cub3d.h"

int map_parse_condition(t_gen_info *info, int i)
{
	if (info->info_string[i][0] == ' '
		|| info->info_string[i][0] == '0'
		|| info->info_string[i][0] == '1')
	{
		return (1);
	}
	return (0);
}
//hier könte man die 0 gleich weg lassen, da am Anfnag ja nur leer oder 1 sein darf?

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
	if (strcomp(str,"NO ") == 1)
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

int get_max_len(char **str, t_gen_info *info)
{
	int len;
	int	i;

	i = 0;
	len = (int)ft_strlen(str[0]);
	while (str[i] != NULL)
	{ 
		if (len < (int)ft_strlen(str[i]))
			len = (int)ft_strlen(str[i]);
		i++;
	}
	info->map_y = i;
	return (len);
}

int set_to_map(t_gen_info *info, char **str)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	info->map = ft_calloc(info->map_y + 1, sizeof(char *));
	if (!info->map)
		error_free_exit("Error\nmalloc", info, INFO_STRING);
	while (str[i] != NULL)
	{
		j = 0;
		x = 0;
		info->map[y] = ft_calloc(info->map_x, sizeof(char));
		//hier machts keinen Unterschied ob  + 1 oder nicht
		if (!info->map[y])
			return (0);
		while (str[i][j] != 0 && str[i][j] != 10 && j < info->map_x)
		{
			ft_memset(&info->map[y][x], str[i][j], 1);
			j++;
			x++;
		}
		printf("xxx	%d", x);
		printf("info->map_x	%d\n", info->map_x);
		// x -= 5;
		while (x < info->map_x)
		{

			info->map[y][x] = '1';
			x++;
		}
		// x -= 1;
		info->map[y][x] = '\0';
		i++;
		y++;
	}
	info->map[y] = NULL;
	return (1);
}
//to long

int	parse_data_info(t_gen_info *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (info->info_string[i][0] != '\0')
	{
		if (init_text_struct(info->info_string[i], info))
			error_free_exit("Error\nmalloc", info, TEXTURE_PATH);
		if (!parse_color_settings(info->info_string[i], info))
			return (0);
		if (map_parse_condition(info, i) == 1)
		{
			info->map_x = get_max_len(&info->info_string[i], info);		
			set_to_map(info, &info->info_string[i]);
			break;
		}
		i++;
	}
	if (!info->floor.set || !info->ceiling.set)
	{
		printf("COLOR SETTING IS MISSING\n");
		return (0);
	}
	if (check_map_valid(info) && map_base_player_check(info))
		return (1);
	error_free_exit("\033[31mMAP IS NOT VALID\033[0m", info, INFO_MAP);
	return (0);
}

void	open_cub_fd(t_gen_info *info, int argc, char *argv[])
{
	if (argc == 1)
	{
		info->fd = open("scene.cub", O_RDONLY);
		if (info->fd == -1)
			error_exit("Error\nfiledescriptor", info);
	}
	else if (argc == 2 && check_file_format(argv[1]))
	{
		info->path = ft_strdup(argv[1]);
		info->fd = open(info->path, O_RDONLY);
		if (info->fd == -1)
			error_exit("Error\nfiledescriptor", info);
	}
	else if (argc == 2 && !check_file_format(argv[1]))
		error_exit("Error\nfile extension is wrong!\n", info);

}

int	init_data_info(t_gen_info *info, char *argv[], int argc)
{
	char	*line;
	int		i;

	open_cub_fd(info, argc, argv);
	info->info_string = (char **)malloc(sizeof(char *) * 250);
	//romys filedescriptor variante segfaultet, weil das fd nimma erreichbar ist...
	if (!info->info_string)
		error_exit("Error\nmalloc", info);
	i = 0;
	line = get_next_line(info->fd);
	while (line)
	{
		info->info_string[i] = ft_strdup(line);
		if (!info->info_string[i])
			error_free_exit("Error\nmalloc",info, INFO_STRING);
		free(line);
		line = get_next_line(info->fd);
		i++;
	}
	free(line);
	if (parse_data_info(info))
		return (1);
	return (0);
}
