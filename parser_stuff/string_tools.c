/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:30:59 by rschleic          #+#    #+#             */
/*   Updated: 2022/06/12 16:58:27 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	split_free(char	***tmp, char ***tmp2, t_gen_info **info, char *str)
{
	int	i;

	i = 0;
	while ((*tmp)[i] != NULL)
	{
		free((*tmp)[i]);
		i++;
	}
	i = 0;
	while ((*tmp2)[i] != NULL)
	{
		free((*tmp2)[i]);
		i++;
	}
	free((*tmp));
	free((*tmp2));
	error_free_exit(str, (*info), TEXTURE_PATH);
}

int	top_bottom_check(t_gen_info *info, int j)
{
	if (info->map[0][j] != '\0')
	{
		if ((info->map[0][j] != ' ' && info->map[0][j] != '1'))
			return (0);
	}
	if (info->map[info->map_y - 1][j] != '\0')
	{
		if ((info->map[info->map_y -1][j] != '1'
			&& info->map[info->map_y -1][j] != ' '))
			return (0);
	}
	return (1);
}

int	strcomp(char *str1, const char *str2)
{
	int	len1;
	int	len2;
	int	index;
	int	i2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen((char *)str2);
	index = 0;
	i2 = 0;
	while (str1[index] == ' ')
		index++;
	// printf("str1: %s\n", &str1[index]);
	// printf("str1: %s\n", str1);
	if (!ft_strncmp(&str1[index], str2, 3))
		return (1);
	return (0);
}
