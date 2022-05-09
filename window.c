/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:42:57 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/05/09 09:42:35 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void create_window(void)
{
    void *mlx;
    void *mlx_win;
    t_window_data img;
    
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, WINDOW_X, WINDOW_Y, "Cube 3-D");
    img.img = mlx_new_image(mlx, WINDOW_X, WINDOW_Y);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_lenght, &img.endian);
    mlx_loop(mlx);
}
