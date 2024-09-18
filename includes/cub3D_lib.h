/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_lib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:20:45 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/18 16:22:04 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_LIB_H
# define CUB3D_LIB_H

/*all includes*/

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/*all defines*/

# define ZERO_INIT 0
# define R 0
# define G 1
# define B 2
# define PI 3.14159265359
# define MAP_WIDTH 6
# define MAP_HEIGHT 5
# define NUM_RAYS 100
# define WIDTH 800
# define HEIGHT 800
# define MOVE_SPEED 0.1
#define ROTATION_SPEED 0.1 // Vitesse de rotation (en radians)
/*all enums*/
enum
{
	PLUS = 61,
	MINUS = 45,
	WHEEL_DOWN = 5,
	W_KEY = 119,
	A_KEY = 97,
	S_KEY = 115,
	D_KEY = 100,
	P_KEY = 112,
	E_KEY = 101,
	ARROW_LEFT = 65361,
	ARROW_UP = 65362,
	ARROW_RIGHT = 65363,
	ARROW_DOWN = 65364,
	LEFT = 1,
	UP = 2,
	RIGHT = 3,
	DOWN = 4,
	X = 0,
	Y = 1,
	ESCAPE = 65307,
	PLEFT = 91,
	PRIGHT = 93,
};

enum			settings
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
};

/*all structures*/

typedef struct s_color
{
	int			f_r;
	int			f_g;
	int			f_b;
	int			c_r;
	int			c_g;
	int			c_b;
	int			i;
	int			j;
}				t_color;

typedef struct s_map
{
	char		*path_no;
	char		*path_so;
	char		*path_we;
	char		*path_ea;

}				t_map;

typedef struct s_file
{
	char		*map_line;
	char		*map_line_cpy;
	char		**tab_data;
	char		**split_settings;
	char		**value;
	int			fd;
}				t_file;

typedef struct s_player
{
	float		fov;
	double		distance;
	double		angle;
	double		radians;
	char		dir;
	double		x;
	double		y;
	double time;    // time of current frame
	double oldTime; // time of previous frame
	double		size_width;
	double		size_height;
	int			map_pos[4096];
	int			arrival_pos[4096];

}				t_player;

typedef struct s_mlx
{
	void		*p_mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_mlx;

typedef struct s_data
{
	t_player	player;
	char		**map_test;
	t_file		*file;
	t_map		*map;
	t_color		*color;
	t_mlx		mlx;
	int			cell_width;
	int			cell_height;
	// int wall;
	// int			ground;
}				t_data;

/*strings functions*/

int				ft_strlen(char *str);
char			*ft_strrchr(const char *str, int searchedChar);
int				ft_strcmp(const char *s1, const char *s2);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
char			*ft_itoa(int nbr);
char			*ft_strdup(const char *s);
char			*ft_strchr(const char *s, int c);
void			ft_putnbr_fd(int n, int fd);
char			**ft_split(char const *s, char c);
char			*ft_strstr(char *haystack, char *needle);
int				ft_strncmp(const char *first, const char *second,
					size_t length);
int				ft_atoi(const char *nbr);
;

/*checker functions*/

void			checker(int argc, char **argv, char **envp);
void			check_envp(char **envp);
void			check_nb_args(int argc);
void			check_extension(char **argv);
int				ft_count_char(char *argv, char c);

/*parsing functions*/

void			file_parser(t_data *data, char *file);
int				open_file(char *file);
void			cpy_map_data(t_data *data);
void			file_cutter(t_data *data);
void			check_order_data(t_data *data);
void			extract_data(t_data *data);
int				extract_settings(t_data *data);
int				detect_data(t_data *data, char *str);
void			set_value(t_data *data, char **split, int sett);
void			check_nb_colors(t_data *data, char **split);

/*free functions*/

void			free_file_struct(t_data *data);
void			free_map_struct(t_data *data);
void			free_split(char **split);

/*utils functions*/

char			*new_alloc(t_data *data, char *ptr, int size);
void			debug(char *msg);

/*error functions*/

void			error_alloc_file(char *msg);
void			error_alloc_mapline(t_data *data, char *msg);
void			error_split_value(t_data *data, char *msg);
void			error_atoi(t_data *data, char *msg);
void			error_read(t_data *data, char *msg);
void			error_open(t_data *data, char *msg);
void			error_split(t_data *data);
void			error_order(t_data *data);

/*init functions*/

void			init_map_struct(t_data *data);
void			init_file_struct(t_data *data);
void			init_color_struct(t_data *data);
int				init_mlx(t_data *data);
/*raycasting functions*/

void			init_player(t_data *data);
double			get_angle_posplayer(char player_dir);
void			ray_cast_radians(t_data *data);
void			img_pix_put(t_data *data, int x, int y, int color);
void			draw_rectangle(t_data *data, int x, int y, int width, int height, int color);
int				update_player_pos(t_data *data,int player_x,int player_y);
int				minimap_render(void *param);
int cpy_map(t_data *data);
int update_player_pos(t_data *data,int player_x,int player_y);
void	draw_rectangle(t_data *data, int x, int y, int width, int height,int color);
int	key_handler(int keycode, t_data *data);
void draw_vector(t_data *data, int pos1[2], int pos2[2], int color);
void draw_map(t_data *data);
void prespective_fn(t_data *data);
#endif
