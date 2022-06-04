/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:30:17 by rschleic          #+#    #+#             */
/*   Updated: 2022/06/04 19:28:11 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_color_val(const char **str)
{
	int	tmp_num;
	int	i;
	int	j;

	i = 0;
	tmp_num = 0;
	while (str[i])
	{
		tmp_num = ft_atoi(str[i]);
		j = 0;
		if (tmp_num < 0)
			return (0);
		while (str[i][j] != 10 && str[i][j] != '\0')
		{
			if (ft_isdigit(str[i][j]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	if (i != 3)
		return (0);
	return (1);
}

void	set_ceiling_values(t_gen_info **info, char **tmp2)
{
	if (!(*info)->ceiling.set)
	{
		(*info)->ceiling.red = ft_atoi((const char *)tmp2[0]);
		(*info)->ceiling.yellow = ft_atoi((const char *)tmp2[1]);
		(*info)->ceiling.blue = ft_atoi((const char *)tmp2[2]);
		(*info)->ceiling.set = true;
	}
	else
		error_free_exit("ERROR\nto many color values", (*info), TEXTURE_PATH);
}

void	set_floor_values(t_gen_info **info, char **tmp2)
{
	if (!(*info)->floor.set)
	{
		(*info)->floor.red = ft_atoi((const char *)tmp2[0]);
		(*info)->floor.yellow = ft_atoi((const char *)tmp2[1]);
		(*info)->floor.blue = ft_atoi((const char *)tmp2[2]);
		(*info)->floor.set = true;
	}
	else
		error_free_exit("ERROR\nto many color values", (*info), TEXTURE_PATH);
}

void	floor_ceiling(char	***tmp, char ***tmp2, t_gen_info **info)
{
	if (strcomp((*tmp)[0], "F"))
	{
		if (d_len_str((*tmp2)) != 3 || d_len_str((*tmp)) != 2)
			split_free(tmp, tmp2, info, "ERROR\ncolor format");
		if (check_color_val((const char **)(*tmp2)) == 0)
			split_free(tmp, tmp2, info, "ERROR\ncolor Input wrong");
		set_floor_values(info, (*tmp2));
	}
	else if (strcomp((*tmp)[0], "C"))
	{
		if (d_len_str((*tmp2)) != 3 || d_len_str((*tmp)) != 2)
			split_free(tmp, tmp2, info, "ERROR\ncolor format");
		if (check_color_val((const char **)(*tmp2)) == 0)
			split_free(tmp, tmp2, info, "ERROR\ncolor input wrong");
		set_ceiling_values(info, (*tmp2));
	}
}

int	split_values(char *str, t_gen_info *info)
{
	int		i;
	int		j;
	char	**tmp;
	char	**tmp2;

	i = 0;
	j = 0;
	tmp = ft_split(str, ' ');
	if (tmp == NULL)
		error_free_exit("ERROR\nsplit", info, TEXTURE_PATH);
	tmp2 = ft_split(tmp[1], ',');
	if (tmp2 == NULL)
	{
		free(tmp);
		error_free_exit("ERROR\nsplit", info, TEXTURE_PATH);
	}
	floor_ceiling(&tmp, &tmp2, &info);
	free_str(tmp);
	free_str(tmp2);
	return (1);
}
