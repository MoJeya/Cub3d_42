/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:50:21 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/05/04 16:58:06 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (1);
	}
	else if(strcomp(str, "SO "))
	{
		info->texture_SO_path = ft_strdup(str + ft_strlen("SO "));
		return (1);
	}
	else if (strcomp(str, "WE "))
	{
		info->texture_WE_path = ft_strdup(str + ft_strlen("WE "));
		return (1);
	}
	else if (strcomp(str, "EA "))
	{
		info->texture_EA_path = ft_strdup(str + ft_strlen("EA "));
		return (1);
	}
	return (0);
}

int pars_data_info(t_gen_info *info)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (info->info_string[i] != NULL)
	{
		init_text_struct(info->info_string[i], info);
		parse_color_settings(info->info_string[i], info);
		if (map_parse_condition(info, i) == 1)
		{
			info->map[j] = ft_strdup(info->info_string[i]);
			j++;
		}	
		i++;
	}
	info->map_height = j - 1;
	if (check_map_valid(info))
		return (1);
	printf("\033[31mMAP IS NOT VALID\033[0m\n");
	return (0);
}

int init_data_info(t_gen_info *info)
{
	int fd;
	char *line;
	int i;
	
	fd = open("scene.cub", O_RDONLY);
	info->info_string = (char **)malloc(sizeof(char *) * 250);
	if (!info->info_string)
		return (0);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		info->info_string[i] = ft_strdup(line);
		i++;
		free(line);
	}
	free(line);
	info->map = (char **)malloc(sizeof(char *) * 250);
	if (!info->map)
		return (0);
	if (pars_data_info(info))
		return (1);
	return (0);
}