/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:30:43 by rschleic          #+#    #+#             */
/*   Updated: 2022/06/13 14:51:16 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	map_parse_condition(t_gen_info *info, int i)
{
	int	j;

	j = 0;
	while (info->info_string[i][j] == ' ')
		j++;
	if (info->info_string[i][j] == '0'
		|| info->info_string[i][j] == '1')
		return (1);
	return (0);
}

int	parse_color_settings(char *str, t_gen_info *info)
{
	if (ft_strchr(str, 'F'))
	{
		if (!split_values(str, info))
			return (0);
		return (1);
	}
	else if (ft_strchr(str, 'C'))
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

	tmp = set_texture(str, x);
	*direction = ft_strtrim(tmp, "\n");
	if (!direction)
		return (0);
	return (1);
}

int	init_text_struct(char **str, t_gen_info *info, int i)
{
	while (str[i] != NULL)
	{
		set_no_so(info, str, i);
		set_we_ea(info, str, i);
		if (info->success > 4)
			return (0);
		i++;
	}
	if (info->success < 4)
		return (0);
	return (1);
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
