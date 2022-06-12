/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:50:16 by rschleic          #+#    #+#             */
/*   Updated: 2022/06/12 14:32:10 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exit(char *str, t_gen_info *info)
{
	if (info->fd != -1)
		close(info->fd);
	if (info->path != NULL)
		free(info->path);
	ft_putendl_fd(str, 2);
	exit(1);
}

void	free_map(t_gen_info *info)
{
	int	i;

	i = 0;
	if (info->map)
	{
		while (info->map[i])
		{
			free(info->map[i]);
			i++;
		}
		free (info->map);
	}
}

void	free_infostring(t_gen_info *info)
{
	int	i;

	i = 0;

	if (info->info_string)
	{
		printf("i: %d\n", i);
		while (info->info_string[i])
		{
			free(info->info_string[i]);
			i++;
		}
		free (info->info_string);
	}
}

void	free_texturepath(t_gen_info *info)
{
	if (info->texture_no_path)
		free(info->texture_no_path);
	if (info->texture_so_path)
		free(info->texture_so_path);
	if (info->texture_we_path)
		free(info->texture_we_path);
	if (info->texture_ea_path)
		free(info->texture_ea_path);
}

void	error_free_exit(char *str, t_gen_info *info, int state)
{
	int	i;

	i = 0;
	close(info->fd);
	if (info->path != NULL)
		free(info->path);
	if (state == INFO_STRING)
	{
		free_infostring(info);
	}
	else if (state == TEXTURE_PATH)
	{
		free_texturepath(info);
		free_infostring(info);
	}
	else if (state == INFO_MAP)
	{
		free_infostring(info);
		free_texturepath(info);
		free_map(info);
	}
	ft_putendl_fd(str, 2);
	exit(1);
}
