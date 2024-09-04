/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:06:23 by whamdi            #+#    #+#             */
/*   Updated: 2024/09/04 13:08:50 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void init_player(t_data *data)
{
	data->player.fov = 60; // fov de 60 degres
	data->player.angle = 0;
	data->player.distance = 0;
	data->wall = 0;
	data->ground = 0;
	data->player.time = 0; //time of current frame
	data->player.oldTime = 0; // time of previous frame
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

void ray_cast_radians(int player_angle, t_data *data)
{
	int i = 0;
	double ray_angle;
	double ray_dir_x;
	double ray_dir_y;
	while(i < NUM_RAYS)
	{
		ray_angle = player_angle - (data->player.fov / 2) + (i * (data->player.fov / NUM_RAYS));
		ray_dir_x = cos(ray_angle);
		ray_dir_y = sin(ray_angle);
		i++;
	}
}

