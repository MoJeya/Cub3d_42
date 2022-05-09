#include "cub3d.h"

# define BUFFER_SIZE 62
//TODO: HERE!!!
// int player_parser(char *str, int i, t_gen_info *info)
// {
// 	int i;

// 	i = 0;
// 	while ()
// }

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
//durch jeden Buchstaben einzeln durchgehen und auch leere Stellen erlauben

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