/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:30:36 by rschleic          #+#    #+#             */
/*   Updated: 2022/06/07 20:24:16 by mjeyavat         ###   ########.fr       */
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
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (info->info_string[i][0] != '\0')
	{
		if (init_text_struct(info->info_string[i], info))
			error_free_exit("ERROR\nmalloc", info, TEXTURE_PATH);
		if (!parse_color_settings(info->info_string[i], info))
			return (0);
		if (map_parse_condition(info, i) == 1)
		{
			if (sides_check(&info->info_string[i]) == 0)
				info->map_x = get_max_len(&info->info_string[i], info);
			else
				break ;
			init_map(info, &info->info_string[i]);
			break ;
		}
		i++;
	}
	if (!info->floor.set || !info->ceiling.set)
		error_free_exit("ERROR\ncolor setting is missing", info, INFO_MAP);
	if (check_map_valid(info) && map_base_player_check(info))
		return (1);
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
		info->fd = open(info->path, O_RDONLY);
		if (info->fd == -1)
			error_exit("Error\nfiledescriptor", info);
	}
	else if (argc == 2 && !check_file_format(argv[1]))
		error_exit("Error\nfile extension is wrong!\n", info);
}

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
	while (line)
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
