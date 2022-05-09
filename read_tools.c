#include "cub3d.h"

# define BUFFER_SIZE 62

int check_file_format(char *argv[])
{
	int i;
	// int j;
	const char *tmp;
	
	i = 0;
	tmp = ft_strchr(argv[1], '.');
	printf("%s\n", tmp);
	if (!ft_strncmp(tmp, ".cub", ft_strlen(".cub") + 1))
	{
		printf("%s\n", tmp);
		return (1);
	}
	return (0);
}

int map_base_player_check(t_gen_info *info)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (info->map[i])
	{
		j = 0;
		while (info->map[i][j] != 10)
		{
			if (ft_isascii(info->map[i][j]))
			{
				// printf("map[%d][%d]: %c\n", i, j, info->map[i][j]);
				if (ft_strchr("NOSW", info->map[i][j]))
					return (1);
				if (!ft_strchr("10 ", info->map[i][j]))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int ft_strlen_nl(char *str)
{
	int len;

	len = 0;
	while (str[len] != '\0' && str[len] != 10)
		len++;
	return (len - 1);
}

int check_map_valid(t_gen_info *info)
{
	int i;
	int j;
	int line_size;
	i = 0;
	j = 0;

	if (ft_strlen(info->map[0]) > ft_strlen(info->map[info->map_height]))
		line_size = ft_strlen(info->map[0]);
	else
		line_size = ft_strlen(info->map[info->map_height]);
	while (j < line_size)
	{
		if (info->map[0][j] != '\n')
		{
			if ((info->map[0][j] != ' ' && info->map[0][j] != '1'))
				return (0);	
		}
		if (info->map[info->map_height][j] != '\0')
		{
			if ((info->map[info->map_height][j] != '1' && info->map[info->map_height][j] != ' '))
				return (0);
		}
		j++;
	}
	//ist hier dabei, dass auch ganz viele leere stellen drin sein dürfen?
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
	if (j == 0)
		return (1);
	return (0);
}
//wie hat mo das gemacht, dass gecheckt wird ob der komplette rand aus 1en besteht?
//alle stellen abgehen

char	*get_next_line(int fd)
{
	char	buffer;
	char	rtn[7000000];
	int		n;
	int		i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	i = 0;
	n = read(fd, &buffer, 1);
	while (n > 0)
	{
		rtn[i++] = buffer;
		if (buffer == '\n')
			break ;
		n = read(fd, &buffer, 1);
	}
	rtn[i] = 0;
	if (n <= 0 && i == 0)
		return (0);
	return (ft_strdup(rtn));
}