/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:30:43 by rschleic          #+#    #+#             */
/*   Updated: 2022/06/04 18:22:28 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	map_parse_condition(t_gen_info *info, int i)
{
	if (info->info_string[i][0] == ' '
		|| info->info_string[i][0] == '0'
		|| info->info_string[i][0] == '1')
	{
		return (1);
	}
	return (0);
}

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

int	store_texture(char *x, char *str, char **direction)
{
	char	*tmp;

	*direction = ft_strdup(str + ft_strlen(x));
	tmp = *direction;
	free (*direction);
	*direction = ft_strtrim(tmp, "\n");
	if (!direction)
		return (1);
	return (0);
}

int	init_text_struct(char *str, t_gen_info *info)
{
	if (strcomp(str, "NO ") == 1)
	{
		if (store_texture("NO ", str, &info->texture_no_path))
			return (1);
	}
	else if (strcomp(str, "SO "))
	{
		if (store_texture("SO ", str, &info->texture_so_path))
			return (1);
	}
	else if (strcomp(str, "WE "))
	{
		if (store_texture("WE ", str, &info->texture_we_path))
			return (1);
	}
	else if (strcomp(str, "EA "))
	{
		if (store_texture("EA ", str, &info->texture_ea_path))
			return (1);
	}
	return (0);
}

int	set_values_to_map(t_gen_info *info, char **str, int *y)
{
	int	j;
	int	x;

	while (str[(*y)] != NULL)
	{
		j = 0;
		x = 0;
		info->map[(*y)] = my_calloc(info->map_x, sizeof(char), info, INFO_MAP);
		while (str[(*y)][j] != 0 && str[(*y)][j] != 10 && j < info->map_x)
		{
			ft_memset(&info->map[(*y)][x], str[(*y)][j], 1);
			j++;
			x++;
		}
		while (x < (info->map_x - 1))
		{
			info->map[(*y)][x] = '1';
			x++;
		}
		info->map[(*y)][x] = '\0';
		(*y)++;
	}
	return ((*y));
}
