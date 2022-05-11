/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:50:16 by rschleic          #+#    #+#             */
/*   Updated: 2022/05/11 11:27:22 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// typedef enum free_code{
// 	INFO_STRING,
// 	TEXTURE_PATH,
// 	F_C,
// 	INFO_MAP,
// }	t_free_code;

void    error_exit(char *str, t_gen_info *info)
{
    if (info->fd != -1)
        close(info->fd);
    free(info->path);
    ft_putendl_fd(str, 2);
    exit(1);
}

void    error_free_exit(char *str, t_gen_info *info, int state)
{
    int i;

    i = 0;
    close(info->fd);
    free(info->path);
    ft_putendl_fd(str, 2);
    if (state == INFO_STRING)
    {
        if (info->info_string)
        {
            while (info->info_string[i])
            {
                free(info->info_string[i]);
                i++;
            }
            free (info->info_string);
        }
    }
    else if (state == TEXTURE_PATH)
    {
        if (info->texture_NO_path)
            free(info->texture_NO_path);
        if (info->texture_SO_path)
            free(info->texture_SO_path);
        if (info->texture_WE_path)
            free(info->texture_WE_path);
        if (info->texture_EA_path)
            free(info->texture_EA_path);
    }
    else if (state == INFO_MAP)
    {
        if (info->info_string)
        {
            while (info->info_string[i])
            {
                free(info->info_string[i]);
                i++;
            }
            free (info->info_string);
        }
        if (info->texture_NO_path)
            free(info->texture_NO_path);
        if (info->texture_SO_path)
            free(info->texture_SO_path);
        if (info->texture_WE_path)
            free(info->texture_WE_path);
        if (info->texture_EA_path)
            free(info->texture_EA_path);
        if (info->map)
        {
            while (info->map[i])
            {
                free(info->map[i]);
                i++;
            }
            free (info->map);
        }
    }
    ft_putendl_fd(str, 2);
    exit(1);   
}
//comments