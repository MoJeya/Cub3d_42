/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:34:15 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/05/09 16:54:39 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen_nl(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && str[len] != 10)
		len++;
	return (len - 1);
}

int	top_bottom_check(t_gen_info *info, int j)
{
	if (info->map[0][j] != '\n')
	{
		if ((info->map[0][j] != ' ' && info->map[0][j] != '1'))
			return (0);
	}
	if (info->map[info->map_height][j] != '\0')
	{
		if ((info->map[info->map_height][j] != '1'
			&& info->map[info->map_height][j] != ' '))
			return (0);
	}
	return (1);
}

int	sides_check(t_gen_info *info)
{
	int	i;
	int	j;
	int	line_size;

	i = 0;
	j = 0;
	while (info->map[i])
	{
		line_size = ft_strlen_nl(info->map[i]);
		if (info->map[i][0] != '1' && info->map[i][0] != ' ')
			j++;
		if (info->map[i][line_size] != '1' && info->map[i][line_size] != ' ')
			j++;
		i++;
	}
	return (j);
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	strcomp(char *str1, const char *str2)
{
	int	len1;
	int	len2;
	int	index;

	len1 = ft_strlen(str1);
	len2 = ft_strlen((char *)str2);
	index = 0;
	while (str1[index] == str2[index] && index <= len1)
	{
		index++;
		if (index == len2)
			return (1);
	}
	return (0);
}

void	split_values(char *str, t_gen_info *info)
{
	int		i;
	int		j;
	char	**tmp;
	char	**tmp2;

	i = 0;
	j = 0;
	tmp = ft_split(str, ' ');
	if (tmp == NULL)
		error_free_exit("ERROR\nsplit", info, -1);
	tmp2 = ft_split(tmp[1], ',');
	if (tmp2 == NULL)
	{
		free(tmp);
		error_free_exit("ERROR\nsplit", info, -1);
	}
	if (strcomp(tmp[0], "F"))
	{
		info->floor.red = ft_atoi((const char *)tmp2[0]);
		info->floor.yellow = ft_atoi((const char *)tmp2[1]);
		info->floor.blue = ft_atoi((const char *)tmp2[2]);
	}
	//hier noch auf richtige rgb werte protecten
	else if (strcomp(tmp[0], "C"))
	{
		info->ceiling.red = ft_atoi((const char *)tmp2[0]);
		info->ceiling.yellow = ft_atoi((const char *)tmp2[1]);
		info->ceiling.blue = ft_atoi((const char *)tmp2[2]);
	}
	//hier noch auf richtige rgb werte protecten
	free_str(tmp);
	free_str(tmp2);
}