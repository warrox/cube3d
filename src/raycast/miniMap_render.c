/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniMap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 10:09:53 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/05 10:33:38 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	cast_ray(t_data *data, double ray_angle, int player_pos[2])
{
	int	hit;
	int	arrival_pos[2];

	double ray_dir_x, ray_dir_y;
	hit = 0;
	int map_x, map_y;
	set_ray_direction(&ray_dir_x, &ray_dir_y, ray_angle);
	data->ray_x = data->player.x;
	data->ray_y = data->player.y;
	while (!hit)
	{
		data->ray_x += ray_dir_x * 0.1;
		data->ray_y += ray_dir_y * 0.1;
		check_ray_hit(data, &hit, &map_x, &map_y);
	}
	calculate_arrival_position(data, data->ray_x, data->ray_y, arrival_pos);
	draw_line_fov_minim(data, player_pos, arrival_pos, 0xFF0000);
}

void	draw_fov(t_data *data)
{
	double	fov;
	double	half_fov;
	int		num_rays;
	double	angle_step;
	double	ray_angle;
	int		player_pos[2];
	int		i;

	fov = 60 * (PI / 180.0);
	half_fov = fov / 2;
	num_rays = 100;
	angle_step = fov / num_rays;
	calculate_player_position(data, player_pos);
	i = 0;
	while (i < num_rays)
	{
		ray_angle = data->player.angle - half_fov + (i * angle_step);
		cast_ray(data, ray_angle, player_pos);
		i++;
	}
}

void	draw_line_fov_minim(t_data *data, int pos1[2], int pos2[2], int color)
{
	
	t_minimap var;
	

	var.x0 = pos1[0];
	var.y0 = pos1[1];
	var.x1 = pos2[0];
	var.y1 = pos2[1];
	var.dx = abs(var.x1 - var.x0);
	var.dy = abs(var.y1 - var.y0);
	var.sx = (var.x0 < var.x1) ? 1 : -1;
	var.sy = (var.y0 < var.y1) ? 1 : -1;
	var.err = var.dx - var.dy;
	while (var.x0 != var.x1 || var.y0 != var.y1)
	{
		img_pix_put(data, var.x0, var.y0, color);
		var.e2 = 2 * var.err;
		if (var.e2 > - var.dy)
		{
			var.err -= var.dy;
			var.x0 += var.sx;
		}
		if (var.e2 < var.dx)
		{
			var.err += var.dx;
			var.y0 += var.sy;
		}
	}
	img_pix_put(data, var.x0, var.y0, color);
}
