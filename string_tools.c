/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:34:15 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/05/02 21:28:39 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

char *ft_str_calloc(int size)
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

char *ft_strchr_nl(char *str)
{
	while (*str != '\0')
	{
		if (*str == '\n')
			return (str);
		str++;
	}
	return (NULL);
}

char *ft_str_join(char **str1, char *str2, int size)
{
	int     i;
	int     j;
	char    *res_str;
	
	i = 0;
	j = 0;
	res_str = ft_str_calloc(ft_strlen((*str1) + 1 + size));
	if (!res_str)
		return (NULL);
	while ((*str1)[i])
	{
		res_str[i] = (*str1)[i];
		i++;
	}
	while (str2[j])
	{
		res_str[i + j] = str2[j];
		j++;
	}
	res_str[i + j] = 0;
	free(*str1);
	return (res_str);
}

char *ft_strdup(char *str)
{
	char *newstr;
	int i;
	
	newstr = ft_str_calloc(ft_strlen(str) + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (str[i])
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = 0;
	return (newstr);
}

int strcomp(char *str1, const char *str2)
{
	int len1;
	int len2;
	int index;

	len1 = ft_strlen(str1);
	len2 = ft_strlen((char *)str2);
	index = 0;
	while (str1[index] == str2[index] && index <= len1)
	{
		// printf("str1: %s\nstr2: %s\n", str1, str2);
		index++;
		if (index == len2)
		{
			// printf("true\n");
			return (1);
		}
	}
	return (0);
	
}