/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:50:16 by rschleic          #+#    #+#             */
/*   Updated: 2022/05/09 16:47:05 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// typedef enum free_code{
// 	INFO_STRING,
// 	TEXTURE_PATH,
// 	FC,
// 	INFO_MAP,
// }	t_free_code;

void    error_exit(char *str, t_gen_info *info)
{
    if (info->fd != -1)
        close(info->fd);
    ft_putendl_fd(str, 2);
    exit(1);
}

void    error_free_exit(char *str, t_gen_info *info, int i)
{
    (void)i;
    close(info->fd);
    ft_putendl_fd(str, 2);
    //free everything up til then according to enum
    //in jedem Fall muss man nochmal double check machen ob auch wirklich schon etwas allociert wurde...
    exit(1);   
}
