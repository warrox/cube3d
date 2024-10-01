/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:06:23 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/01 21:51:59 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"
#include <stdio.h>

void	img_pix_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	if (x < 1 || x >= WIDTH - 1 || y < 1 || y >= HEIGHT - 1)
		return ;
	dst = data->mlx.addr + (y * data->mlx.line_length + x
			* (data->mlx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_player(t_data *data)
{
	data->player.fov = 60; // fov de 60 degres
	data->player.angle = 0;
	data->player.distance = 0;
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
	if (player_dir == 'S')
	{
		return (PI / 2);
	}
	if (player_dir == 'N')
	{
		return (3 * PI / 2);
	}
	if (player_dir == 'W')
	{
		return (PI);
	}
	return (0);
}




void draw_vertical_line(t_data *data, int x, int start, int end, t_texture *texture, int wall_height, double hit_x)
{
    int y;
    int tex_y;
    double step;
    double texture_pos;
    int tex_x;

    // Calcul de la position correcte dans la texture en fonction de hit_x (la position où le rayon a touché le mur)
	tex_x = (int)(hit_x * texture->width) % texture->width;

    // Dessiner le ciel (au-dessus du mur)
    y = 0;
    while (y < start)
    {
        img_pix_put(data, x, y, data->file->color->conv_c); // Couleur du ciel
        y++;
    }

    // Facteur d'échelle : combien de pixels de la texture pour un pixel du mur
    step = (double)texture->height / wall_height;

    // Position de départ dans la texture
    texture_pos = (start - HEIGHT / 2 + wall_height / 2) * step;

    // Dessiner le mur entre 'start' et 'end'
    while (y <= end)
    {
        tex_y = (int)texture_pos % texture->height;
        int color = *(unsigned int *)(texture->addr + (tex_y * texture->line_lengh + tex_x * (texture->bpp / 8)));
        img_pix_put(data, x, y, color); // Dessiner le pixel du mur
        texture_pos += step;
        y++;
    }

    // Dessiner le sol (en dessous du mur)
    while (y < HEIGHT)
    {
        img_pix_put(data, x, y, data->file->color->conv_f); // Couleur du sol
        y++;
    }
}

void render_3d(t_data *data, double distance, int x, t_texture *texture, double hit_x)
{
    if (distance <= 0)
        return;

    int wall_height = (int)(HEIGHT / distance);
    int draw_start = -wall_height / 2 + HEIGHT / 2;
    if (draw_start < 0) draw_start = 0;
    
    int draw_end = wall_height / 2 + HEIGHT / 2;
    if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;

    draw_vertical_line(data, x, draw_start, draw_end, texture, wall_height, hit_x);
}
double send_ray(t_data *data, double ray_angle, double fov_radians, double *ray_x, double *ray_y, int i, int num_rays)
{
    double ray_dir_x;
    double ray_dir_y;
    int map_x;
    int map_y;
    int hit;
    double distance = 0;
    double hit_x = 0;
	t_texture *texture;

    ray_dir_x = cos(ray_angle);
    ray_dir_y = sin(ray_angle);
    *ray_x = data->player.x;
    *ray_y = data->player.y;
    hit = 0;
    while (!hit)
    {
        *ray_x += ray_dir_x * 0.01;
        *ray_y += ray_dir_y * 0.01;

        map_x = (int)*ray_x;
        map_y = (int)*ray_y;

        if (map_x >= 0 && map_x < data->file->max_len && map_y >= 0 && map_y < data->file->line_map && data->file->map[map_y][map_x] == '1')
        {
            hit = 1;

            // Calculer la direction du mur touché et la texture à utiliser
            if (fabs(ray_dir_x) > fabs(ray_dir_y))
            {
                if (ray_dir_x > 0)
				{
					texture = &data->ea;
				}
                else
				{
					texture = &data->we;
				}
                hit_x = *ray_y - floor(*ray_y);
            }
            else
            {
                if (ray_dir_y > 0)
				{
					texture = &data->so;
				}
                else
                    texture = &data->no;
                hit_x = *ray_x - floor(*ray_x);
            }

            double angle = ((i - (num_rays / 2)) * data->player.fov) / num_rays;
            double angle_rad = angle * (PI / 180);
            distance = sqrt(pow(*ray_x - data->player.x, 2) + pow(*ray_y - data->player.y, 2)) * cos(angle_rad);
            render_3d(data, distance, i, texture, hit_x);
            return distance;
        }

        if (map_x < 0 || map_x >= data->file->max_len || map_y < 0 || map_y >= data->file->line_map)
        {
            hit = 1;
        }
    }
    return 0;
}
void ray_cast_radians(t_data *data)
{
    double ray_angle;
    
	int num_rays = 1000;
	
	double ray_x;
	double ray_y;

	// **New var ** //
	int center_plane[2];
	center_plane[0] = WIDTH /2 ;
	center_plane[1] = HEIGHT /2;
	// ** //
	double fov_radians = data->player.fov * (PI / 180.0); // Conversion du FOV en radians
    double angle_step = fov_radians / num_rays; // Pas d'angle entre chaque rayon
    	
	int i = 0;
    while (i++ < num_rays)
    {
		ray_angle = data->player.angle - (fov_radians / 2) + (i * angle_step);
		data->player.distance = send_ray(data, ray_angle, fov_radians, &ray_x, &ray_y, i, num_rays); 
    }
	//draw mini map + fov de la minimap
	draw_map(data);
	draw_fov(data);
}
