/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:14:41 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/05/09 14:42:24 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
char *ft_strdup(char *s1)
{
	char *newstr;
	int i;
	
	newstr = ft_calloc(ft_strlen(s1) + 1);
	if (!newstr)
		return (NULL);
	printf("here!\n");
	i = 0;
	while (s1[i])
	{
		printf("%c\n", s1[i]);
		newstr[i] = s1[i];
		i++;
	}
	newstr[i] = 0;
	printf("%s\n", newstr);
	return (newstr);
}