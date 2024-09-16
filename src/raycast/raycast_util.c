/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:06:23 by whamdi            #+#    #+#             */
/*   Updated: 2024/09/16 16:43:09 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	img_pix_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 1 || x >= WIDTH - 1 || y < 1 || y >= HEIGHT - 1)
		return ;
	dst = data->mlx.addr + (y * data->mlx.line_length + x
			* (data->mlx.bits_per_pixel / 8));
	// printf("COLOR : %d\n", color);
	// fflush(stdout);
	*(unsigned int *)dst = color;
}

void	init_player(t_data *data)
{
	data->player.fov = 60; // fov de 60 degres
	data->player.angle = 0;
	data->player.distance = 0;
	// data->wall = 0;
	// data->ground = 0;
	data->player.time = 0;    // time of current frame
	data->player.oldtime = 0; // time of previous frame
	data->player.x = -1;
	data->player.y = -1;
}

double	get_angle_posplayer(char player_dir)
{
	if (player_dir == 'E')
	{
		return (0);
	}
	if (player_dir == 'N')
	{
		return (PI / 2);
	}
	if (player_dir == 'S')
	{
		return (3 * PI / 2);
	}
	if (player_dir == 'W')
	{
		return (PI);
	}
	return (0);
}

void	ray_cast_radians(t_data *data)
{
	double	ray_angle;
	double	ray_dir_x;
	double	ray_dir_y;
	int		ray_x;
	int		ray_y;

	ray_angle = data->player.angle;
	// printf("ray angle : %f\n",ray_angle);
	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	for (int len = 0; len < 1000; len++)
	{ // Longueur maximale du rayon
		ray_x = (data->player.x * data->cell_width) + (data->cell_width
				+ (int)(ray_dir_x * len));
		ray_x = (data->player.x * data->cell_width + data->player.size_height)
			+ (int)(ray_dir_x * len);
		ray_y = (data->player.y * data->cell_height + data->player.size_width
				/ 2) + (int)(ray_dir_y * len);
		// printf("ray x : %d\n",ray_x);
		// printf("ray y : %d\n",ray_y);
		// if dans la fenetre
		if (ray_x >= 0 && ray_x < WIDTH && ray_y >= 0 && ray_y < HEIGHT)
		{
			// printf("GOIN BEFORE PIXPUT\n");
			img_pix_put(data, ray_x, ray_y, 0x00FF00); // Vert
		}
	}
	// for (int x = 0; x < WIDTH; x++) {
	// 	for (int y = 0; y < HEIGHT; y++) {
	//        img_pix_put(data, x, y, 0xFFFFFF); // Blanc
	// 	}
	// }
}
