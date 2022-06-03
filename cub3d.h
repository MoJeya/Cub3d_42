
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

# define TILES_W 16
# define TILES_H 16
# define screenWidth 800
# define screenHeight 600
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
	int				map_pos_x;
	int				map_pos_y;
	double			prep_wall_dist;
	double			dis_to_wall;
	mlx_image_t		*p_img;
}t_player;

typedef struct s_color
{
	bool set;
	int red;
	int yellow;
	int blue;
	
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
	t_player 			player;
	t_raycast			raycast;
	t_frames			frame;
	int					hit; // was there a wallhit;
	int					side; // was there a NS or a EW wall hit?
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
}t_gen_info;

/********************PARSER***************************/
int		parse_data_info(t_gen_info *info);
int		init_map(t_gen_info *info, char **str);
int		set_values_to_map(t_gen_info *info, char **str, int *y);
int		get_max_len(char **str, t_gen_info *info);
int		init_text_struct(char *str, t_gen_info *info);
int		parse_color_settings(char *str, t_gen_info *info);
int		map_parse_condition(t_gen_info *info, int i);

/********************WINDOW_MLX***************************/
int32_t	create_window(t_gen_info *info);

/********************TOOLS************************/
char	*ft_strchr_nl(char *str);
int		split_values(char *str, t_gen_info *info);
int		strcomp(char *str1, const char *str2);
int		sides_check(t_gen_info *info);
int		top_bottom_check(t_gen_info *info, int j);
/*****************READ_TOOLS****************************/
char	*get_next_line(int fd);
int		check_map_valid(t_gen_info *info);
int		map_base_player_check(t_gen_info *info);
int		check_file_format(char *path);
int		init_data_info(t_gen_info *info, char *argv[], int argc);
void	set_direction_player(t_gen_info *info);
void	get_textures(t_gen_info *info);
// void player_dir_init(t_gen_info *info);

/*****************ERROR****************************/
void	error_exit(char *str, t_gen_info *info);
void	error_free_exit(char *str, t_gen_info *info, int i);
void	*my_calloc(size_t count, size_t size, t_gen_info *info, int state);

/****************HELPER FUNCTIONS**********************/
int		d_len_str(char **str);

/****************3D************************************/
void	rotate_mouse(t_gen_info *info);
void	render_wrld(void *param);
void	player_movment(t_gen_info *info, int map_posx, int map_posy);
// void main_loop(mlx_image_t *map);

void	draw_minimap(t_gen_info *info);

#endif