/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_lib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:20:45 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/05 13:23:05 by whamdi           ###   ########.fr       */
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

/*all defines*/

# define ZERO_INIT 0
# define NULL_INIT NULL
# define PI 3.14159265359
# define MAP_WIDTH 6
# define MAP_HEIGHT 5
# define NUM_RAYS 100
# define g_value 10
# define w_value 10
# define WIDTH	800
# define HEIGHT 800

#define MOVE_SPEED 5 
#define W_KEY 119
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100
#define ARROW_LEFT 65361
#define ARROW_UP 65362
#define ARROW_RIGHT 65363
#define ARROW_DOWN 65364
/*all structures*/

typedef struct s_map
{
	char 	*line_map;
	int	fd;
}			t_map;

typedef struct s_player
{
	float fov;
	int distance;
	int angle;
	int radians;
	char dir;
	int x;
	int y;
	double time; //time of current frame
	double oldTime; //time of previous frame
}				t_player;
typedef struct s_mlx
{
	void	*p_mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_mlx;
typedef struct s_data
{
	t_player player;
	t_mlx mlx;
	t_map	*map;
	int wall;
	int ground;

}				t_data;

/*strings functions*/

int			ft_strlen(char *str);
char		*ft_strrchr(const char *str, int searchedChar);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
char		*ft_itoa(int nbr);
char		*ft_strdup(const char *s);
char		*ft_strchr(const char *s, int c);
void		ft_putnbr_fd(int n, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strstr(char *haystack, char *needle);

/*checker functions*/

void	checker(int argc, char **argv, char **envp);
void	check_envp(char **envp);
void	check_nb_args(int argc);
void	check_extension(char **argv);
int	ft_count_dot(char *argv, char c);

/*parsing functions*/

void	map_parser(t_data *data, char *file);
void	init_map_struct(t_data *data);
int	open_file(char *file);

/*free functions*/

void	free_map_struct(t_data *data);

/*RAYCASTING functions*/
void init_player(t_data *data);
double get_angle_posplayer(char player_dir);
void ray_cast_radians(t_data *data);
void	img_pix_put(t_data *data, int x, int y, int color);
#endif
