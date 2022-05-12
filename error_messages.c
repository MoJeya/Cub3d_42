/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:50:16 by rschleic          #+#    #+#             */
/*   Updated: 2022/05/12 16:59:26 by rschleic         ###   ########.fr       */
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
	if (info->texture_NO_path)
		free(info->texture_NO_path);
	if (info->texture_SO_path)
		free(info->texture_SO_path);
	if (info->texture_WE_path)
		free(info->texture_WE_path);
	if (info->texture_EA_path)
		free(info->texture_EA_path);
}

void	error_free_exit(char *str, t_gen_info *info, int state)
{
	int	i;

	i = 0;
	close(info->fd);
	if (info->path != NULL)
		free(info->path);
	if (state == INFO_STRING)
		free_infostring(info);
	else if (state == TEXTURE_PATH)
	{
		free_infostring(info);
		free_texturepath(info);
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
