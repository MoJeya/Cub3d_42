/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapwall_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:49:58 by rschleic          #+#    #+#             */
/*   Updated: 2022/06/13 14:50:30 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	t_b_check(char **info_str, t_gen_info *info)
{
	int	i;

	i = 0;
	if (info_str[0] == NULL && info_str[info->map_y - 1] == NULL)
		return (0);
	while (info_str[0][i] != '\0')
	{
		if (info_str[0][i] == '0')
			return (0);
		i++;
	}
	i = 0;
	while (info_str[info->map_y - 1][i] != '\0')
	{
		if (info_str[info->map_y - 1][i] == '0')
			return (0);
		i++;
	}
	return (1);
}

int	sides_check(char **info_str)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = 0;
	x = 0;
	while (info_str[i] != NULL)
	{
		x = 0;
		while (info_str[i][x] == ' ')
			x++;
		if (info_str[i][x] != '1' && info_str[i][x] != ' ')
			j++;
		if ((info_str[i][ft_strlen(info_str[i]) - 2] != '1'))
			j++;
		i++;
	}
	return (j);
}

int	check_if_open(char *str_check, char *str_top, char *str_bottom)
{
	int	i;

	i = 0;
	while (str_check[i] != '\0')
	{
		if (str_check[i] == '0')
		{
			if (str_top[i] == ' ' || i > (int)ft_strlen(str_top))
				return (0);
			else if (str_bottom[i] == ' ' || i > (int)ft_strlen(str_bottom))
				return (0);
		}
		i++;
	}
	return (1);
}

int	side_len_check(char **info_str)
{
	int	i;

	i = 1;
	while (info_str[i] != NULL)
	{
		if (info_str[i + 1] != NULL)
		{
			if (check_if_open(info_str[i],
					info_str[i - 1], info_str[i + 1]) == 0)
			{
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	top_bottom_valid(t_gen_info *info, int i, bool *mapper)
{
	info->map_x = get_max_len(&info->info_string[i], info);
	if (t_b_check(&info->info_string[i], info) == 0)
		return (0);
	(*mapper) = true;
	return (1);
}
