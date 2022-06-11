/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:30:43 by rschleic          #+#    #+#             */
/*   Updated: 2022/06/11 17:20:47 by mjeyavat         ###   ########.fr       */
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
	if (ft_strchr(str, 'F'))
	{
		if (!split_values(str, info))
			return (0);
		// printf("found F\n");
		return (1);
	}
	else if (ft_strchr(str, 'C'))
	{
		if (!split_values(str, info))
			return (0);
		// printf("found C\n");
		return (1);
	}
	// printf("retunrn 1\n");
	return (1);
}

int	store_texture(char *x, char *str, char **direction)
{
	char	*tmp;

	*direction = ft_strdup(set_texture(str, x));
	tmp = *direction;
	free (*direction);
	*direction = ft_strtrim(tmp, "\n");
	// printf("direction	%s\n", *direction);
	if (!direction)
		return (0);
	return (1);
}

int	init_text_struct(char **str, t_gen_info *info, int i)
{
	while (str[i] != NULL)
	{
		if (info->check[0] == false)
		{
			// printf("true? = %d\n",)
			if (strcomp(str[i], "NO "))
			{
				if (store_texture("NO ", str[i], &info->texture_no_path))
				{
					printf("NO was found!\n");
					info->success++;
					info->check[0] = true;
				}
			}	
		}
		if (info->check[1] == false)
		{
			if (strcomp(str[i], "SO "))
			{
				if (store_texture("SO ", str[i], &info->texture_so_path))
				{
					printf("SO was found!\n");
					info->check[1] = true;
					info->success++;
				}
			}
		}
		if (info->check[2] == false)
		{
			if (strcomp(str[i], "WE "))
			{
				if (store_texture("WE ", str[i], &info->texture_we_path))
				{
					printf("WE was found!\n");
					info->check[2] = true;
					info->success++;
				}
			}
		}
		if (i == 1)
			printf("ea: %s\n", str[i]);
		if (info->check[3] == false)
		{
			if (strcomp(str[i], "EA "))
			{
				if (store_texture("EA ", str[i], &info->texture_ea_path))
				{
					printf("EA was found!\n");
					info->check[3] = true;
					info->success++;	
				}
			}
		}
		if (info->success == 4)
		{
			printf("success: %d\n", info->success);
			return (1);
		}
		printf("i: %d\n", i);
		i++;
	}
	printf("not success: %d\n", info->success);
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
