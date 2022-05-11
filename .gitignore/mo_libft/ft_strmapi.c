/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:49:13 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/05/03 16:16:19 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_s;
	size_t	index;

	index = 0;
	if (!s || !f)
		return (NULL);
	new_s = (char *)malloc((ft_strlen((char *)s) + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	while (s[index] != '\0')
	{
		new_s[index] = f(index, s[index]);
		index++;
	}
	new_s[index] = '\0';
	return (new_s);
}
