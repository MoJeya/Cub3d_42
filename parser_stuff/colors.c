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
			error_free_exit("ERROR\ncolor format", info, TEXTURE_PATH);
		}
		if (check_color_val((const char **)tmp2) == 0)
		{
			free_str(tmp);
			free_str(tmp2);
			error_free_exit("ERROR\ncolor input wrong", info, TEXTURE_PATH);
		}
		if (!info->floor.set)
		{
			info->floor.red = ft_atoi((const char *)tmp2[0]);
			info->floor.yellow = ft_atoi((const char *)tmp2[1]);
			info->floor.blue = ft_atoi((const char *)tmp2[2]);
			info->floor.set = true;
		}
		else
			error_free_exit("ERROR\nto many color values", info, TEXTURE_PATH);
	}
	else if (strcomp(tmp[0], "C"))
	{
		if (d_len_str(tmp2) != 3 || d_len_str(tmp) != 2)
		{
			free(tmp);
			free(tmp2);
			error_free_exit("ERROR\ncolor format", info, TEXTURE_PATH);
		}
		if (check_color_val((const char **)tmp2) == 0)
		{
			free_str(tmp);
			free_str(tmp2);
			error_free_exit("ERROR\ncolor input wrong", info, TEXTURE_PATH);
		}
		if (!info->ceiling.set)
		{
			info->ceiling.red = ft_atoi((const char *)tmp2[0]);
			info->ceiling.yellow = ft_atoi((const char *)tmp2[1]);
			info->ceiling.blue = ft_atoi((const char *)tmp2[2]);
			info->ceiling.set = true;
		}
		else
			error_free_exit("ERROR\nto many color values", info, TEXTURE_PATH);
	}
	free_str(tmp);
	free_str(tmp2);
	return (1);
}
//wayyyo to long
