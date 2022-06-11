/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:29:42 by rschleic          #+#    #+#             */
/*   Updated: 2022/06/11 20:14:34 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include "NEW_MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <sys/time.h>
# include <string.h>

# define TILES_W 8
# define TILES_H 8
# define SCREEN_W 800
# define SCREEN_H 600
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_ESC 53
# define RIGHT 124
# define DOWN 125
# define PI 3.1415926535
# define BUFFER_SIZE 42

typedef enum free_code{
	INFO_STRING,
	TEXTURE_PATH,
	INFO_MAP,
}	t_free_code;
//new

typedef struct s_point
{
	double	x;
	double	y;
}t_point;

typedef struct s_raycast
{
	double		camera_x;
	t_point		dir;
	t_point		side_dist;
	t_point		delta_dist;
	int			draw_start;
	int			draw_end;
}t_raycast;

typedef struct s_player
{
	t_point			pos;
	t_point			dir;
	t_point			plane;
	char			looking;
	int				step_x;
	int				step_y;
	double			prep_wall_dist;
	double			dis_to_wall;
	mlx_image_t		*p_img;
}t_player;

typedef struct s_color
{
	bool	set;
	int		red;
	int		yellow;
	int		blue;
}t_color;

typedef struct s_frames
{
	double	time;
	double	old_time;
	double	frame_time;
	double	movment_speed;
	double	rotation_speed;
}t_frames;

typedef struct s_gen_info
{
	mlx_t				*mlx;
	mlx_image_t			*m_img;
	mlx_texture_t		*m_wall;
	mlx_texture_t		*player_img;
	mlx_texture_t		*back_g;
	xpm_t				*xpm[4];
	t_player			player;
	t_raycast			raycast;
	t_frames			frame;
	int					hit;
	int					side;
	int					line_h;
	int					map_x;
	int					map_y;
	int					win_x;
	int					win_y;
	int					fd;
	t_color				ceiling;
	t_color				floor;
	char				*path;
	char				**map;
	char				*texture_no_path;
	char				*texture_so_path;
	char				*texture_we_path;
	char				*texture_ea_path;
	char				**info_string;
	int					mouse_x;
	int					mouse_y;
	bool				mini_mp;
	int					success;
	bool				check[4];
}t_gen_info;

/********************PARSER***************************/
int		parse_data_info(t_gen_info *info);
int		init_map(t_gen_info *info, char **str);
int		set_values_to_map(t_gen_info *info, char **str, int *y);
int		get_max_len(char **str, t_gen_info *info);
int		init_text_struct(char **str, t_gen_info *info, int i);
int		parse_color_settings(char *str, t_gen_info *info);
int		map_parse_condition(t_gen_info *info, int i);

/********************WINDOW_MLX***************************/
int32_t	create_window(t_gen_info *info);

/********************TOOLS************************/
char	*ft_strchr_nl(char *str);
int		split_values(char *str, t_gen_info *info);
int		strcomp(char *str1, const char *str2);
int		sides_check(char **info_str);
int		top_bottom_check(t_gen_info *info, int j);

/*****************READ_TOOLS****************************/
char	*get_next_line(int fd);
int		check_map_valid(t_gen_info *info);
int		map_base_player_check(t_gen_info *info);
int		check_file_format(char *path);
int		init_data_info(t_gen_info *info, char *argv[], int argc);
void	set_direction_player(t_gen_info *info);
// void player_dir_init(t_gen_info *info);

/*****************ERROR****************************/
void	error_exit(char *str, t_gen_info *info);
void	error_free_exit(char *str, t_gen_info *info, int i);
void	*my_calloc(size_t count, size_t size, t_gen_info *info, int state);

/****************HELPER FUNCTIONS**********************/
int		d_len_str(char **str);
void	split_free(char	***tmp, char ***tmp2, t_gen_info **info, char *str);
void	free_str(char **str);
int		create_trgb(int t, int r, int g, int b);
int		get_textures(t_gen_info *info);
void	init_genaral_info(t_gen_info *info);

/****************3D************************************/
void	rotate_mouse(t_gen_info *info);
void	render_wrld(void *param);
void	player_movment(t_gen_info *info);
void	draw_minimap(t_gen_info *info);
void	minimap_movement(t_gen_info *info);

/***********************RAYCAST MOVMENT******************/
void	set_startval(int x, t_gen_info *info);
void	set_delta_dist(t_gen_info *info);

/****************PLAYER MOVMENT CALCULATION************/
void	rotate_mouse(t_gen_info *info);
void	rotate_player(t_gen_info *info, int dir);
bool	check_for_wall(t_gen_info *info, int i, int end_value, t_point vec);
void	calc_perp_walldist(t_gen_info *info);
void	set_line_height(t_gen_info *info);
void	dda_calc(t_gen_info *info, int map_pos_x, int map_pos_y);
void	set_step(t_gen_info *info, int map_pos_x, int map_pos_y);
void	init_raycast_info(t_gen_info *info);
int		store_texture(char *x, char *str, char **direction);
bool	file_name_handler(char *pfile);
char	*set_texture(char *str, const char *dir);
int		t_b_check(char **info_str, t_gen_info *info);
int		side_len_check(char **info_str);
void	set_success(t_gen_info *info);
void	set_no_so(t_gen_info *info, char **str, int i);
void	set_we_ea(t_gen_info *info, char **str, int i);
#endif