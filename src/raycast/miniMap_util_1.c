/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniMap_util_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 10:41:31 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/05 10:48:22 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	draw_fov(t_data *data)
{
	t_minimap	d;
	double		half_fov;
	int			player_pos[2];

	d.fov = 60 * (PI / 180.0);
	half_fov = d.fov / 2;
	d.num_rays = 100;
	d.angle_step = d.fov / d.num_rays;
	calculate_player_position(data, player_pos);
	d.i = 0;
	while (d.i < d.num_rays)
	{
		d.ray_angle = data->player.angle - half_fov + (d.i * d.angle_step);
		cast_ray(data, d.ray_angle, player_pos);
		d.i++;
	}
}
