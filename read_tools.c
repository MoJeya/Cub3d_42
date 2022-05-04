#include "cub3d.h"

# define BUFFER_SIZE 62

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
	//TODO : HERE side checks have to be done!
	while (info->map[i])
	{
		line_size = ft_strlen(info->map[i]) - 3;
		printf("line: %s\nlast char: %c\nline size: %d\n", info->map[i], info->map[i][line_size], line_size);
		if (info->map[i][0] != '1' && info->map[i][0] != ' ')
			return (0);
		if (info->map[i][line_size] != '1' && info->map[i][line_size] != ' ')
			return (0);
		i++;
	}
	return (1);
}

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