/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:34:15 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/05/04 15:49:45 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"


void free_str(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int strcomp(char *str1, const char *str2)
{
	int len1;
	int len2;
	int index;

	len1 = ft_strlen(str1);
	len2 = ft_strlen((char *)str2);
	index = 0;
	while (str1[index] == str2[index] && index <= len1)
	{
		// printf("str1: %s\nstr2: %s\n", str1, str2);
		index++;
		if (index == len2)
		{
			// printf("true\n");
			return (1);
		}
	}
	return (0);
}
	
void split_values(char *str, t_gen_info *info)
{
	int i;
	int j;
	char **tmp;
	char **tmp2;

	i = 0;
	j = 0;
	tmp = ft_split(str, ' ');
	tmp2 = ft_split(tmp[1], ',');
	if (strcomp(tmp[0], "F"))
	{
		info->floor.red = ft_atoi((const char *)tmp2[0]);
		info->floor.yellow = ft_atoi((const char *)tmp2[1]);
		info->floor.blue = ft_atoi((const char *)tmp2[2]);
	}
	else if (strcomp(tmp[0], "C"))
	{
		info->celing.red = ft_atoi((const char *)tmp2[0]);
		info->celing.yellow = ft_atoi((const char *)tmp2[1]);
		info->celing.blue = ft_atoi((const char *)tmp2[2]);
	}
	free_str(tmp);
	free_str(tmp2);
}