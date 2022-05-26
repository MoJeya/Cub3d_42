#include "../cub3d.h"

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

int	sides_check(t_gen_info *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (info->map[i] != NULL && i < info->map_y)
	{
		if (info->map[i][0] != '1' && info->map[i][0] != ' ')
			j++;
		if (info->map[i][info->map_x - 2] != '1'
				&& info->map[i][info->map_x - 2] != ' ')
			j++;
		i++;
	}
	return (j);
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
