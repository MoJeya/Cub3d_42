/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:30:43 by rschleic          #+#    #+#             */
/*   Updated: 2022/06/11 13:06:28 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

	*direction = ft_strdup(set_texture(str, x));
	tmp = *direction;
	free (*direction);
	*direction = ft_strtrim(tmp, "\n");
	printf("direction	%s\n", *direction);
	if (!direction)
		return (0);
	return (1);
}

int	init_text_struct(char **str, t_gen_info *info, int i)
{
	bool	check[4];

	check[0] = false;
	check[1] = false;
	check[2] = false;
	check[3] = false;
	printf("i start\n");
	while (str[i] != NULL && i < 4)
	{
		if (check[0] == false)
		{
			if (strcomp(str[i], "NO "))
			{
				if (store_texture("NO ", str[i], &info->texture_no_path))
				{
					check[0] = true;
					info->success++;
				}
			}	
		}
		else if (check[1] == false)
		{
			if (strcomp(str[i], "SO "))
			{
				if (store_texture("SO ", str[i], &info->texture_so_path))
				{
					check[1] = true;
					info->success++;
				}
			} 
		}
		else if (check[2] == false)
		{
			if (strcomp(str[i], "WE "))
			{
				if (store_texture("WE ", str[i], &info->texture_we_path))
				{
					check[2] = true;
					info->success++;
				}
			}
		}
		else if (check[3] == false)
		{
			if (strcomp(str[i], "EA "))
			{
				if (store_texture("EA ", str[i], &info->texture_ea_path))
				{
					check[3] = true;
					info->success++;	
				}
			}
		}
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
