#include "../cub3d.h"

int d_len_str(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

int	check_file_format(char *path)
{
	int			i;
	const char	*tmp;

	i = ft_strlen(path);
	if (i <= 4)
		return (0);
	tmp = (const char *)&path[(i - 4)];
	if (!ft_strncmp(tmp, ".cub", ft_strlen(".cub") + 1))
		return (1);
	return (0);
}

int	map_base_player_check(t_gen_info *info)
{
	int		i;
	int		j;
	int		player_cnt;
	bool	right_type;

	i = 0;
	j = 0;
	player_cnt = 0;
	right_type = true;
	while (info->map[i] != NULL)
	{
		j = 0;
		while (info->map[i][j] != 10 && info->map[i][j] != '\0')
		{
			if (ft_isascii(info->map[i][j]))
			{
				if (ft_strchr("NESW", info->map[i][j]))
				{
					info->player.looking = info->map[i][j];
					// printf("player direction: %c\n", info->player.looking);
					info->player.pos.y = (float)i + 0.5;
					info->player.pos.x = (float)j + 0.5;
					info->player.map_pos_x = j;
					info->player.map_pos_y = i;
					info->map[i][j] = '0';
					player_cnt++;
				}
				if (!ft_strchr("10 ", info->map[i][j]) && player_cnt != 1)
				{
					right_type = false;
					break ;
				}
				if (info->map[i][j] == ' ')
					info->map[i][j] = '1';
			}
			j++;
		}
		i++;
	}
	if (player_cnt == 1 && right_type == true)
		return (1);
	return (0);
}
//to long

int	check_map_valid(t_gen_info *info)
{
	int		j;

	j = 0;
	while (j < info->map_x)
	{
		if (top_bottom_check(info, j) == 0)
			return (0);
		j++;
	}
	if (sides_check(info) == 0)
	{
		info->win_x = (info->map_x - 1) * 25;
		info->win_y = info->map_y * 25;
		return (1);
	}
	return (0);
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
