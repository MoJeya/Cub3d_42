/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:50:21 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/05/02 21:32:30 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int init_map_struct(t_gen_info *info)
{
	
}

int init_text_struct(char *str, t_gen_info *info)
{
	if (strcomp(str,"NO") == 1)
	{
		info->texture_NO_path = ft_strdup(str);
		return (1);
	}
	else if(strcomp(str, "SO"))
	{
		info->texture_SO_path = ft_strdup(str);
		return (1);
	}
	else if (strcomp(str, "WE"))
	{
		info->texture_WE_path = ft_strdup(str);
		return (1);
	}
	else if (strcomp(str, "EA"))
	{
		info->texture_EA_path = ft_strdup(str);
		return (1);
	}
	return (0);
}

int init_data_info(t_gen_info *info)
{
	int fd = open("scene.cub", O_RDONLY);
	char *line;
	int i;
		
	info->info_string = (char **)malloc(sizeof(char *) * 250);
	if (!info->info_string)
		return (0);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		// printf("%s", line);
		info->info_string[i] = ft_strdup(line);
		i++;
		free(line);
	}
	free(line);

	//for testing
	i = 0;
	while (info->info_string[i] != NULL)
	{
		printf("%s", info->info_string[i]);
		init_text_struct(info->info_string[i], info)
		i++;
	}
	printf("\n%s\n", info->texture_SO_path);
	printf("\n%s\n", info->texture_NO_path);
	printf("\n%s\n", info->texture_WE_path);
	printf("\n%s\n", info->texture_EA_path);
	return (0);
}