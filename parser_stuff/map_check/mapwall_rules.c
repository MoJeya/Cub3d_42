/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapwall_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:49:58 by rschleic          #+#    #+#             */
/*   Updated: 2022/06/11 21:09:57 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
		if (info_str[i][0] != '1' && info_str[i][0] != ' ')
			x++;
		if ((info_str[i][ft_strlen(info_str[i]) - 2] != '1')
			&& (info_str[i][ft_strlen(info_str[i]) - 2] != ' '))
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
			if (str_top[i] == ' ')
			{
				// printf("failed!\n");
				return (0);
			}
			else if (str_bottom[i] == ' ')
			{
				// printf("failed!\n");
				return (0);
			}
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
				printf("not so success!\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}
