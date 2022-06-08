#include "../cub3d.h"

bool	file_name_handler(char *path_to_file)
{
	char	*filename;
	int		i;
	int		p;

	i = 0;
	p = 0;
	filename = NULL;
	if (path_to_file != NULL)
	{
		filename = ft_strdup(ft_strnstr(path_to_file,
					"maps/", ft_strlen("map/") + 1) + ft_strlen("map/") + 1);
		if (filename[0] == '.')
		{
			free(filename);
			return (false);
		}
		while (filename[i] != '\0')
		{
			if (filename[i] == '.')
				p++;
			if (p > 1)
			{
				free(filename);
				return (false);
			}
			i++;
		}
		free(filename);
		return (true);
	}
	free(filename);
	return (false);
}