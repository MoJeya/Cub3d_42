/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:09:23 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/05/03 13:59:47 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_calloc(int size)
{
	char *tmp;
	int i;

	i = 0;
	tmp = malloc(size);
	if (!tmp)
		return (NULL);
	while (i < size)
		tmp[i++] = 0;
	return (tmp);
}
