/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ray_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:46:16 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/05 14:06:11 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void init_ray_variables(t_data *data, double ray_angle)
{
    data->ray_dir_x = cos(ray_angle);
    data->ray_dir_y = sin(ray_angle);
    data->ray_x = data->player.x;
    data->ray_y = data->player.y;
}

int check_wall_hit(t_data *data, double *ray_x, double *ray_y, int *map_x, int *map_y)
{
    *map_x = (int)*ray_x;
    *map_y = (int)*ray_y;
    return (data->file->map[*map_y][*map_x] == 'W');
}

void handle_hit_texture(t_data *data, double *ray_x, double *ray_y, double ray_dir_x, double ray_dir_y, double ray_angle, double *hit_x, t_texture **texture)
{
    if (data->file->map[(int)*ray_y][(int)*ray_x] == '2')
        *texture = &data->texture[1];
    else
        *texture = &data->texture[0];
    
    *hit_x = *ray_x - floor(*ray_x);
}
