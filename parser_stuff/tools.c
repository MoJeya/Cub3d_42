/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:31:35 by rschleic          #+#    #+#             */
/*   Updated: 2022/06/13 15:46:53 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

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
