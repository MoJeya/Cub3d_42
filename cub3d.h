/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:15:59 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/05/02 21:31:45 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define WINDOW_X 850
# define WINDOW_Y 850
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_ESC 53



typedef struct s_point
{
	int		x;
	int		y;
}t_point;

typedef struct s_player
{
	t_point		p_pos;
	int			dis_to_wall;
}t_player;

typedef struct s_gen_info
{
	t_player *player;
	int		window_x;
	int		window_y;
	int		f_color_r;
	int		f_color_g;
	int		f_color_b;
	char 	**map;
	char	*texture_NO_path;
	char	*texture_SO_path;
	char	*texture_WE_path;
	char	*texture_EA_path;
	char	**info_string;
}t_gen_info;

typedef struct s_window_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_lenght;
	int endian;
}t_window_data;

void creat_window(void);





/********************STIRNG_TOOLS************************/
int ft_strlen(char *str);
char *ft_str_calloc(int size);
char *ft_str_join(char **str1, char *str2, int size);
char *ft_strdup(char *str);
char *ft_strchr_nl(char *str);
char *get_next_line(int fd);
int strcomp(char *str1, const char *str2);

int init_data_info(t_gen_info *info);

#endif