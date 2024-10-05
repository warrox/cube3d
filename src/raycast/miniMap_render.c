/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniMap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 10:09:53 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/05 10:53:05 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	cast_ray(t_data *data, double ray_angle, int player_pos[2])
{
	t_minimap	d;
	int			arrival_pos[2];

	d.hit = 0;
	set_ray_direction(&d.ray_dir_x, &d.ray_dir_y, ray_angle);
	data->ray_x = data->player.x;
	data->ray_y = data->player.y;
	while (!d.hit)
	{
		data->ray_x += d.ray_dir_x * 0.1;
		data->ray_y += d.ray_dir_y * 0.1;
		check_ray_hit(data, &d.hit, &d.map_x, &d.map_y);
	}
	calculate_arrival_position(data, data->ray_x, data->ray_y, arrival_pos);
	draw_line_fov_minim(data, player_pos, arrival_pos, 0xFF0000);
}

void	set_line_direction(t_minimap *var)
{
	if (var->x0 < var->x1)
		var->sx = 1;
	else
		var->sx = -1;
	if (var->y0 < var->y1)
		var->sy = 1;
	else
		var->sy = -1;
}

void	calculate_error(t_minimap *var)
{
	var->e2 = 2 * var->err;
	if (var->e2 > -var->dy)
	{
		var->err -= var->dy;
		var->x0 += var->sx;
	}
	if (var->e2 < var->dx)
	{
		var->err += var->dx;
		var->y0 += var->sy;
	}
}

void	draw_line_step(t_data *data, t_minimap *var, int color)
{
	while (var->x0 != var->x1 || var->y0 != var->y1)
	{
		img_pix_put(data, var->x0, var->y0, color);
		calculate_error(var);
	}
	img_pix_put(data, var->x0, var->y0, color);
}

void	draw_line_fov_minim(t_data *data, int pos1[2], int pos2[2], int color)
{
	t_minimap	var;

	var.x0 = pos1[0];
	var.y0 = pos1[1];
	var.x1 = pos2[0];
	var.y1 = pos2[1];
	var.dx = abs(var.x1 - var.x0);
	var.dy = abs(var.y1 - var.y0);
	var.err = var.dx - var.dy;
	set_line_direction(&var);
	draw_line_step(data, &var, color);
}
