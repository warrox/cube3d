/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:06:23 by whamdi            #+#    #+#             */
/*   Updated: 2024/09/05 11:11:19 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"
#include <stdio.h>

void init_player(t_data *data)
{
	data->player.fov = 60; // fov de 60 degres
	data->player.angle = 0;
	data->player.distance = 0;
	data->wall = 0;
	data->ground = 0;
	data->player.time = 0; //time of current frame
	data->player.oldTime = 0; // time of previous frame
	data->player.x = 0;
	data->player.y = 0;
}

double get_angle_posplayer(char player_dir)
{
	if(player_dir == 'E')
	{
		return(0);
	}
	if(player_dir == 'N')
	{
		return(PI/2);
	}
	if(player_dir == 'S')
	{
		return(3 * PI / 2);
	}
	if(player_dir == 'W')
	{
		return(PI);
	}
	return(0);
}

void ray_cast_radians(t_data *data)
{
	double ray_angle = data->player.angle;
	// printf("ray angle : %f\n",ray_angle);
    double ray_dir_x = cos(ray_angle);
    double ray_dir_y = sin(ray_angle);

    for (int len = 0; len < 100; len++) { // Longueur maximale du rayon
        int ray_x = data->player.x + (int)(ray_dir_x * len);
        int ray_y = data->player.y + (int)(ray_dir_y * len);
		// printf("ray x : %d\n",ray_x);
		// printf("ray y : %d\n",ray_y);
        //if dans la fenetre
		if (ray_x >= 0 && ray_x < WIDTH && ray_y >= 0 && ray_y < HEIGHT) {
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
