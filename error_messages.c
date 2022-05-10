/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:50:16 by rschleic          #+#    #+#             */
/*   Updated: 2022/05/10 09:54:58 by rschleic         ###   ########.fr       */
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
    ft_putendl_fd(str, 2);
    exit(1);
}

void    error_free_exit(char *str, t_gen_info *info, int state)
{
    close(info->fd);
    ft_putendl_fd(str, 2);
    //free everything up til then according to enum
    //in jedem Fall muss man nochmal double check machen ob auch wirklich schon etwas allociert wurde...
    if (state == INFO_STRING)
    {
        //MOs doule pointer free function
        //hier checken ob in den einzelnen info strings uberhaupt etwas drin steht
    }
    else if (state == TEXTURE_PATH)
    {
        //MOs doule pointer free function fur die INFO_STRIGS
        /* ->free diese falls vorhanden
        char		*texture_NO_path;
	    char		*texture_SO_path;
	    char		*texture_WE_path;
	    char		*texture_EA_path;
        */
    }
    else if (state == F_C)
    {
        //MOs doule pointer free function fur die INFO_STRIGS
        /* 
        char		*texture_NO_path;
	    char		*texture_SO_path;
	    char		*texture_WE_path;
	    char		*texture_EA_path;
        --> that all for sure  */    
          
    }//denn fall brauch es dann gar nicht, habe das in der split selbst gehandelt
    else if (state == INFO_MAP)
    {
        //MOs doule pointer free function fur info_strings
        /* 
        char		*texture_NO_path;
	    char		*texture_SO_path;
	    char		*texture_WE_path;
	    char		*texture_EA_path;
        --> that all for sure  */
         //MOs doule pointer free function fur map->info
    }
    exit(1);   
}
//also 3 teilige free function
