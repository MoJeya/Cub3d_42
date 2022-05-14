
#include "../cub3d.h"

int check_color_val(const char **str)
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
		{
			perror("ERROR\nNO NEGATIVE VALUES ALLOWED!\n");
			return (0);
		}
		while (str[i][j] != 10 && str[i][j] != '\0')
		{
			if (ft_isdigit(str[i][j]) == 0)
			{
				printf("ERROR\nNOT A NUMBER\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	if (i != 3)
	{
		printf("ERROR\nNOT ENOUGH VALUES\n");
		return (0);
	}
	return (1);
}
//to long

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
		if (info->map[i][info->map_x-1] != '1' && info->map[i][info->map_x-1] != ' ')
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
	if (strcomp(tmp[0], "F"))
	{
		if (d_len_str(tmp2) != 3 || d_len_str(tmp) != 2) 
		{
			free(tmp);
			free(tmp2);
			printf("ERROR\nCOLOR FORMAT IS NOT RIGHT\n");
			return (0);
		}
		if (check_color_val((const char **)tmp2) == 0)
		{
			free_str(tmp);
			free_str(tmp2);
			return (0);
		}
		if (!info->floor.set)
		{
			info->floor.red = ft_atoi((const char *)tmp2[0]);
			info->floor.yellow = ft_atoi((const char *)tmp2[1]);
			info->floor.blue = ft_atoi((const char *)tmp2[2]);
			info->floor.set = true;
		}
		else
		{
			printf("ERROR\nTO MANY COLOR VALUES\n");
			return (0);
		}
	}
	else if (strcomp(tmp[0], "C"))
	{
		if (d_len_str(tmp2) != 3 || d_len_str(tmp) != 2)
		{
			free(tmp);
			free(tmp2);
			printf("ERROR\nCOLOR FORMAT IS NOT RIGHT\n");
			return (0);
		}
		if (check_color_val((const char **)tmp2) == 0)
		{
			free_str(tmp);
			free_str(tmp2);
			return (0);
		}
		if (!info->ceiling.set)
		{
			info->ceiling.red = ft_atoi((const char *)tmp2[0]);
			info->ceiling.yellow = ft_atoi((const char *)tmp2[1]);
			info->ceiling.blue = ft_atoi((const char *)tmp2[2]);
			info->ceiling.set = true;
		}
		else
		{
			printf("ERROR\nTO MANY COLOR VALES\n");
			return (0);
		}
	}
	free_str(tmp);
	free_str(tmp2);
	return (1);
}
//wayyyo to long
