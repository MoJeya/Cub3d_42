#include "../cub3d.h"

bool	file_name_handler(char *pfile)
{
	char	*fname;
	int		i;
	int		p;

	i = 0;
	p = 0;
	fname = NULL;
	fname = ft_strdup(ft_strnstr(pfile, "maps/", ft_strlen("map/") + 1)
			+ ft_strlen("map/") + 1);
	while (fname[i] != '\0' && pfile != NULL)
	{
		if (fname[0] == '.')
		{
			free(fname);
			return (false);
		}
		if (fname[i] == '.')
			p++;
		i++;
	}
	free(fname);
	if (p == 1)
		return (true);
	return (false);
}

char	*set_texture(char *str, const char *dir)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	while (!ft_strchr(dir, str[i]))
		i++;
	tmp = ft_strdup(str + i);
	while (tmp[j] != '\0')
	{
		if (tmp[j] == '.')
			return (&tmp[j]);
		j++;
	}
	return (NULL);
}
