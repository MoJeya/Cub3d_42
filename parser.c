
#include "cub3d.h"

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
//hier könte man die 0 gleich weg lassen?
//da am Anfnag ja nur leer oder 1 sein darf?

int parse_color_settings(char *str, t_gen_info *info)
{
	if (!ft_strncmp(str, "F ", ft_strlen("F ")))
	{
		split_values(str, info);
		return (1);
	}
	else if (!ft_strncmp(str, "C ", ft_strlen("C ")))
	{
		split_values(str, info);
		return (1);
	}
	return (0);
}

int init_text_struct(char *str, t_gen_info *info)
{
	if (strcomp(str,"NO ") == 1)
	{
		info->texture_NO_path = ft_strdup(str + ft_strlen("NO "));
		if (!info->texture_NO_path)
				return (1);
	}
	else if(strcomp(str, "SO "))
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

int parse_data_info(t_gen_info *info)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (info->info_string[i] != NULL)
	//evtl while (info->info_string[i][0] != '\0')?
	{
		if(init_text_struct(info->info_string[i], info))
			error_free_exit("Error\nmalloc", info, TEXTURE_PATH);
		parse_color_settings(info->info_string[i], info);
		if (map_parse_condition(info, i) == 1)
		{
			info->map[j] = ft_strdup(info->info_string[i]);
			if (!info->map[j])
				error_free_exit("Error\nmalloc", info, INFO_MAP);	
			j++;
		}
		i++;
	}
	info->map_height = j - 1;
	if (check_map_valid(info) && map_base_player_check(info))
		return (1);
	error_free_exit("\033[31mMAP IS NOT VALID\033[0m", info, INFO_MAP);
	return (0);
}

int init_data_info(t_gen_info *info, char *argv[], int argc)
{
	char *line;
	int i;
	
	if (argc == 1)
	{
		info->fd = open("scene.cub", O_RDONLY);
    	if (info->fd == -1)
			error_exit("Error\nfiledescriptor", info);
	}
	else if (argc == 2 && check_file_format(argv))
	{
		info->path = ft_strdup(argv[1]);
		printf("%s\n", info->path);
		info->fd = open(argv[1], O_RDONLY);
    	if (info->fd == -1)
     		error_exit("Error\nfiledescriptor", info);
	}
	//den Block in eine eigene function
	else if (argc == 2 && !check_file_format(argv))
		error_exit("Error\nfile extension is wrong!", info);
	info->info_string = (char **)malloc(sizeof(char *) * 250);
	//hier noch eine Lösung überlegen, wie man die Größe bestimmt
	//eine simple zählfunktion, die lediglich die y-Achse der map zählt?
	if (!info->info_string)
		error_exit("Error\nmalloc", info);
		//mit ft_aclloc wird das hier unnotig... aber dann fehlt fd
	i = 0;
	while ((line = get_next_line(info->fd)))
	//kann man so ein while statement schreiben ???
	//was passiert wenn gnl failed?
	{
		info->info_string[i] = ft_strdup(line);
		if(!info->info_string[i])
			error_free_exit("Error\nmalloc",info, INFO_STRING);
			//oder simple variante und nur error_exit?
			//wenn wir mein ft_calloc hernehmen dann wird da schon ne message geprinted
		i++;
		free(line);
	}
	free(line);
	info->map = (char **)malloc(sizeof(char *) * 250);
	//hier noch eine Lösung überlegen, wie man die Größe bestimmt
	//eine simple zählfunktion, die lediglich die y-Achse der map zählt?
	if (!info->map)
		error_free_exit("Error\nmalloc",info, INFO_STRING);
	if (parse_data_info(info))
		return (1);
	return (0);
}
//stimmt das jetzt alles mit den return values?