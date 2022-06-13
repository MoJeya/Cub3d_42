/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:37:46 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/06/13 14:51:12 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	mapper_and_color(t_gen_info *info, bool mapper)
{
	if (!info->floor.set || !info->ceiling.set)
		error_free_exit("ERROR\ncolor setting is missing", info, INFO_MAP);
	if (mapper == true)
	{
		if (map_base_player_check(info))
			return (1);
		else
			error_free_exit("\033[31mTO MANY PLAYERS\033[0m", info, INFO_MAP);
	}
	else
	{
		info->map = NULL;
		error_free_exit("\033[31mMAP IS NOT VALID\033[0m", info, INFO_MAP);
	}
	return (0);
}

void	texture_parsing(t_gen_info *info)
{
	int	i;

	i = 0;
	while (info->info_string[i][0] != '\0')
	{	
		if (ft_strchr(" NOSEW", info->info_string[i][0]))
		{
			if (init_text_struct(&info->info_string[i] - i, info, i) == 0)
				error_free_exit("ERROR\ntexture path", info, TEXTURE_PATH);
			else
				break ;
		}
		i++;
	}
}

void	set_no_so(t_gen_info *info, char **str, int i)
{
	if (strcomp(str[i], "NO "))
	{
		if (store_texture("NO ", str[i], &info->texture_no_path))
		{
			info->success++;
		}
	}
	if (strcomp(str[i], "SO "))
	{
		if (store_texture("SO ", str[i], &info->texture_so_path))
		{
			info->success++;
		}
	}
}

void	set_we_ea(t_gen_info *info, char **str, int i)
{
	if (strcomp(str[i], "WE "))
	{
		if (store_texture("WE ", str[i], &info->texture_we_path))
		{
			info->success++;
		}
	}
	if (strcomp(str[i], "EA "))
	{
		if (store_texture("EA ", str[i], &info->texture_ea_path))
		{
			info->success++;
		}
	}
}
