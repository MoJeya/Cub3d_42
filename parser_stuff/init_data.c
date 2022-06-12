/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:30:36 by rschleic          #+#    #+#             */
/*   Updated: 2022/06/12 16:27:24 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_map(t_gen_info *info, char **str)
{
	int	y;

	y = 0;
	info->map = my_calloc(info->map_y + 1, sizeof(char *), info, INFO_MAP);
	y = set_values_to_map(info, str, &y);
	info->map[y] = NULL;
	return (1);
}

int	parse_data_info(t_gen_info *info)
{
	int		i;
	int		j;
	bool	mapper;

	i = 0;
	j = 0;
	mapper = false;
	while (info->info_string[i][0] != '\0')
	{	
		if (ft_strchr(" NOSEW", info->info_string[i][0]))
		{
			if (init_text_struct(&info->info_string[i]-i, info, i) == 0)
			{
				printf("XXX\n");
				error_free_exit("ERROR\ntexture path", info, TEXTURE_PATH);
			}
			else
				break ;
		}
		i++;
	}
	i = 0;
	while (info->info_string[i][0] != '\0')
	{
		if (!parse_color_settings(info->info_string[i], info))
			return (0);
		if (map_parse_condition(info, i) == 1)
		{
			if (side_len_check(&info->info_string[i]) == 1)
			{
				info->map_x = get_max_len(&info->info_string[i], info);
				if (t_b_check(&info->info_string[i], info) == 0)
					break ;
				mapper = true;
			}	
			else
				break ;
			init_map(info, &info->info_string[i]);
			break ;
		}
		i++;
	}
	if (!info->floor.set || !info->ceiling.set)
		error_free_exit("ERROR\ncolor setting is missing", info, INFO_MAP);
	if (mapper == true)
	{
		if (map_base_player_check(info))
			return (1);
	}
	info->map = NULL;
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
		if (file_name_handler(info->path) == true)
		{
			info->fd = open(info->path, O_RDONLY);
			if (info->fd == -1)
				error_exit("Error\nfiledescriptor", info);
			free(info->path);
		}
		else
			error_exit("Error\nfile extension is wrong!\n", info);
	}
	else if (argc == 2 && !check_file_format(argv[1]))
		error_exit("Error\nfile extension is wrong!\n", info);
}
//aber es enstehen auf jeden fall oepn file descriptors?!

int	count_y(int tmp)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(tmp);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(tmp);
	}
	i++;
	free(line);
	close(tmp);
	return (i);
}

int	init_data_info(t_gen_info *info, char *argv[], int argc)
{
	char	*line;
	int		i;

	open_cub_fd(info, argc, argv);
	info->info_string = (char **)malloc(sizeof(char *) * count_y(info->fd));
	if (!info->info_string)
		error_exit("Error\nmalloc", info);
	open_cub_fd(info, argc, argv);
	i = 0;
	line = get_next_line(info->fd);
	if (line == NULL)
		return (0);
	while (line != NULL)
	{
		info->info_string[i] = ft_strdup(line);
		if (!info->info_string[i])
			error_free_exit("Error\nmalloc", info, INFO_STRING);
		free(line);
		line = get_next_line(info->fd);
		i++;
	}
	info->info_string[i] = NULL;
	if (parse_data_info(info))
		return (1);
	return (0);
}
