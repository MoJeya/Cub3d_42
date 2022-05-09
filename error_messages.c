/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:50:16 by rschleic          #+#    #+#             */
/*   Updated: 2022/05/09 14:43:44 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    error_exit(char *str, t_gen_info *info)
{
    if (info->fd != -1)
        close(info->fd);
    ft_putendl_fd(str, 2);
    exit(1);
    //strerror//perror
}

void    error_free_exit(char *str, t_gen_info *info, int i)
{
    (void)i;
    close(info->fd);
    ft_putendl_fd(str, 2);
    //free everything up til then
    exit(1);   
}
//das wird unsere generelle map free function!


//noch eine functiond die nur freet
//dann ruft man einmal free udn einmale rror message print aus 
//besser!

//bei allen error free exit muss gesschaut werden welche werte aus info bis dato gefreet werden müssen