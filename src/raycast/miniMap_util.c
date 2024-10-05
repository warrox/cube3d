/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniMap_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 10:10:16 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/05 10:13:08 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void calculate_player_position(t_data *data, int player_pos[2])
{
    player_pos[0] = data->player.x * data->cell_width;
    player_pos[1] = data->player.y * data->cell_height;
}

void set_ray_direction(double *ray_dir_x, double *ray_dir_y, double ray_angle)
{
    *ray_dir_x = cos(ray_angle);
    *ray_dir_y = sin(ray_angle);
}

int is_ray_out_of_bounds(t_data *data, int map_x, int map_y)
{
    return (map_x < 0 || map_x >= data->file->max_len || map_y < 0 || map_y >= data->file->line_map);
}

void check_ray_hit(t_data *data, int *hit, double ray_x, double ray_y, int *map_x, int *map_y)
{
    *map_x = (int)ray_x;
    *map_y = (int)ray_y;

    if (data->file->map[*map_y][*map_x] == '1' || is_ray_out_of_bounds(data, *map_x, *map_y))
    {
        *hit = 1;
    }
}

void calculate_arrival_position(t_data *data, double ray_x, double ray_y, int arrival_pos[2])
{
    arrival_pos[0] = ray_x * data->cell_width;
    arrival_pos[1] = ray_y * data->cell_height;
}


