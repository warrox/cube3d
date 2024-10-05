/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniMap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 10:09:53 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/05 10:11:05 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3D_lib.h"

void cast_ray(t_data *data, double ray_angle, int player_pos[2])
{
    double ray_dir_x, ray_dir_y, ray_x, ray_y;
    int hit = 0;
    int map_x, map_y;

    set_ray_direction(&ray_dir_x, &ray_dir_y, ray_angle);

    ray_x = data->player.x;
    ray_y = data->player.y;

    while (!hit)
    {
        ray_x += ray_dir_x * 0.1;
        ray_y += ray_dir_y * 0.1;
        check_ray_hit(data, &hit, ray_x, ray_y, &map_x, &map_y);
    }

    int arrival_pos[2];
    calculate_arrival_position(data, ray_x, ray_y, arrival_pos);
    draw_line_fov_minim(data, player_pos, arrival_pos, 0xFF0000);
}

void draw_fov(t_data *data)
{
    double fov = 60 * (PI / 180.0);
    double half_fov = fov / 2;
    int num_rays = 100;
    double angle_step = fov / num_rays;
    double ray_angle;

    int player_pos[2];
    calculate_player_position(data, player_pos);

    int i = 0;
    while (i < num_rays)
    {
        ray_angle = data->player.angle - half_fov + (i * angle_step);
        cast_ray(data, ray_angle, player_pos);
        i++;
    }
}

void draw_line_fov_minim(t_data *data, int pos1[2], int pos2[2], int color)
{
    int x0 = pos1[0];
    int y0 = pos1[1];
    int x1 = pos2[0];
    int y1 = pos2[1];

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;
    int e2;

    while (x0 != x1 || y0 != y1)
    {
        img_pix_put(data, x0, y0, color);
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
    img_pix_put(data, x0, y0, color);
}

