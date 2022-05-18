#include "cub3d.h"

void	*my_calloc(size_t count, size_t size, t_gen_info *info, int state)
{
	size_t	counter;
	void	*ptr;

	counter = 0;
	ptr = malloc(count * size);
	if (ptr == NULL)
		error_free_exit("ERROR\nmalloc", info, state);
	while (counter < count * size)
	{
		((char *)ptr)[counter] = 0;
		counter++;
	}
	return (ptr);
}

int	get_max_len(char **str, t_gen_info *info)
{
	int	len;
	int	i;

	i = 0;
	len = (int)ft_strlen(str[0]);
	while (str[i] != NULL)
	{
		if (len < (int)ft_strlen(str[i]))
			len = (int)ft_strlen(str[i]);
		i++;
	}
	info->map_y = i;
	return (len);
}