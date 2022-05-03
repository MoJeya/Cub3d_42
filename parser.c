/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:50:21 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/05/03 19:04:37 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int init_data_info(t_gen_info *info)
{
	int fd = open("scene.cub", O_RDONLY);
	char *line;
	int i;
	int j;
	info->info_string = (char **)malloc(sizeof(char *) * 250);
	if (!info->info_string)
		return (0);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		info->info_string[i] = ft_strdup(line);
		i++;
		free(line);
	}
	free(line);

	/**for testing*/
	i = 0;
	j = 0;
	info->map = (char **)malloc(sizeof(char *) * 250);
	if (!info->map)
		return (0);
	while (info->info_string[i] != NULL)
	{
		// printf("%s", info->info_string[i]);
		init_text_struct(info->info_string[i], info);
		parse_color_settings(info->info_string[i], info);
		
		// if ()
		// {
		// 	info->map[j] = ft_strdup(info->info_string[i]);
		// 	printf("%s", info->map[j]);
		// 	j++;
		// }	
		// parse_map(info->info_string[i], info);
		i++;
	}
	printf("\n");
	printf("\n%s\n", info->texture_SO_path);
	printf("\n%s\n", info->texture_NO_path);
	printf("\n%s\n", info->texture_WE_path);
	printf("\n%s\n", info->texture_EA_path);
	printf("\nF:\nred:%s\nyellow:%s\nblue:%s\n", info->f_color_r, info->f_color_g, info->f_color_b);
	printf("\nC:\nred:%s\nyellow:%s\nblue:%s\n", info->c_color_r, info->c_color_g, info->c_color_b);	
	return (0);
}