
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

# define TILES_W 25
# define TILES_H 25
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_ESC 53
# define RIGHT 124
# define DOWN 125
# define PI 3.1415926535

typedef enum free_code{
	INFO_STRING,
	TEXTURE_PATH,
	INFO_MAP,
}	t_free_code;
//new

typedef struct s_point
{
	float		x;
	float		y;
	float		delta_x;
	float		delta_y;
	float		angle;
}t_point;

typedef struct s_player
{
	t_point			pos;
	double			dis_to_wall;
	mlx_image_t		*p_img;
	char			looking;
}t_player;

typedef struct s_color
{
	bool set;
	int red;
	int yellow;
	int blue;
	
}t_color;

typedef struct s_gen_info
{
	t_player 		player;
	mlx_t			*mlx;
	int			map_size_total;
	int			map_x;
	int			map_y;
	int			win_x;
	int			win_y;
	int			map_height;
	int			map_widht;
	int			fd;
	t_color		ceiling;
	t_color		floor;
	char		*path;
	char 		**map;
	char		*texture_NO_path;
	char		*texture_SO_path;
	char		*texture_WE_path;
	char		*texture_EA_path;
	char		**info_string;
}t_gen_info;


/********************WINDOW_MLX***************************/
int32_t	create_window(t_gen_info *info);

/********************STIRNG_TOOLS************************/
char	*ft_strchr_nl(char *str);
int		split_values(char *str, t_gen_info *info);
int		strcomp(char *str1, const char *str2);
int		sides_check(t_gen_info *info);
int		top_bottom_check(t_gen_info *info, int j);
/*****************READ_TOOLS****************************/
char *get_next_line(int fd);
int check_map_valid(t_gen_info *info);
int map_base_player_check(t_gen_info *info);
int check_file_format(char *path);
int init_data_info(t_gen_info *info, char *argv[], int argc);

/*****************ERROR****************************/
void    error_exit(char *str, t_gen_info *info);
void    error_free_exit(char *str, t_gen_info *info, int i);

/****************HELPER FUNCTIONS**********************/
int d_len_str(char **str);


#endif