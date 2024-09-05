/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_lib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:20:45 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/05 11:27:31 by cyferrei         ###   ########.fr       */
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
# define PI 3.14159265359
# define MAP_WIDTH 6
# define MAP_HEIGHT 5
# define NUM_RAYS 100
# define g_value 10
# define w_value 10

/*all structures*/

typedef struct s_map
{
	char		*map_line_cpy;
	char		**data_tab;
	int			fd;
}				t_map;

typedef struct s_player
{
	int			fov;
	int			distance;
	int			angle;
	int			radians;
}				t_player;

typedef struct s_data
{
	t_player	player;
	t_map		*map;
	int			wall;
	int			ground;
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

/*checker functions*/

void			checker(int argc, char **argv, char **envp);
void			check_envp(char **envp);
void			check_nb_args(int argc);
void			check_extension(char **argv);
int				ft_count_char(char *argv, char c);

/*parsing functions*/

void			file_parser(t_data *data, char *file);
void			init_map_struct(t_data *data);
int				open_file(char *file);
void			cpy_map_data(t_data *data, char *map_line);
void			file_cutter(t_data *data);
void			check_order_data(t_data *data);

/*free functions*/

void			free_map_struct(t_data *data);
void			free_split(t_data *data);

/*utils functions*/

char			*new_alloc(t_data *data, char *ptr, int size);
void			debug(char *msg);

/*error functions*/

void			error_msg(char *msg);
void			error_read(t_data *data, char *map_line, char *msg);
void			error_open(t_data *data, char *map_line);
void			error_cpy(t_data *data, char *map_line);
void			error_split(t_data *data);
void			error_order(t_data *data);

#endif