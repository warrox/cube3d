/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:06:23 by whamdi            #+#    #+#             */
/*   Updated: 2024/09/30 09:32:46 by whamdi           ###   ########.fr       */
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




void draw_vertical_line(t_data *data, int x, int start, int end, int wall_color)
{
    int y;

    // Vérifier que la colonne x est dans les limites de l'écran
    if (x < 0 || x >= WIDTH)
        return;

    // 1. Dessiner le ciel (en bleu clair) au-dessus du mur
    y = 0;
    while (y < start)
    {
        if (y >= 0 && y < HEIGHT)
        {
            img_pix_put(data, x, y, data->file->color->conv_c); // Couleur du ciel (bleu clair)
        }
        y++;
    }

    // 2. Dessiner le mur entre 'start' et 'end'
    while (y <= end)
    {
        if (y >= 0 && y < HEIGHT)
        {
            img_pix_put(data, x, y, wall_color); // Couleur du mur
        }
        y++;
    }

    // 3. Dessiner le sol (en marron) en dessous du mur
    while (y < HEIGHT)
    {
        if (y >= 0 && y < HEIGHT)
        {
            img_pix_put(data, x, y, data->file->color->conv_f); // Couleur du sol (marron)
        }
        y++;
    }
}
void render_3d(t_data *data, double distance, int x)
{
    int wall_height = (int)(HEIGHT / distance);
    int draw_start = -wall_height / 2 + HEIGHT / 2;
    if (draw_start < 0) draw_start = 0;
    
    int draw_end = wall_height / 2 + HEIGHT / 2;
    if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;
	draw_vertical_line(data,x ,draw_start, draw_end, 0x6B5729);
}



double send_ray(t_data *data, double ray_angle, double fov_radians, double *ray_x, double *ray_y, int i, int num_rays)
{
    double ray_dir_x;
    double ray_dir_y;
    int map_x;
    int map_y;
    int hit;
    double distance = 0;
    double angle_rad = 0;

    // Direction du rayon (composantes x et y)
    ray_dir_x = cos(ray_angle);
    ray_dir_y = sin(ray_angle);

    // Initialisation des coordonnées du rayon (commence à la position du joueur)
    *ray_x = data->player.x;
    *ray_y = data->player.y;
    hit = 0;

    // Parcourir le rayon jusqu'à rencontrer un mur "1"
    while (!hit)
    {
        *ray_x += ray_dir_x * 0.01;
        *ray_y += ray_dir_y * 0.01;

        // Convertir les coordonnées réelles en coordonnées de la carte (entier)
        map_x = (int)*ray_x;
        map_y = (int)*ray_y;

        // Vérifier si le rayon touche un mur
        if (map_x >= 0 && map_x < data->file->max_len && map_y >= 0 && map_y < data->file->line_map && data->file->map[map_y][map_x] == '1')
        {
            hit = 1; // Rayon a touché un mur

            // Déterminer la direction du mur touché
            if (fabs(ray_dir_x) > fabs(ray_dir_y))
            {
                if (ray_dir_x > 0)
                {
                    printf("Rayon %d: Direction Est\n", i);
                }
                else
                {
                    printf("Rayon %d: Direction Ouest\n", i);
                }
            }
            else
            {
                if (ray_dir_y > 0)
                {
                    printf("Rayon %d: Direction Sud\n", i);
                }
                else
                {
                    printf("Rayon %d: Direction Nord\n", i);
                }
            }

            // Calculer la distance corrigée avec l'angle du rayon
            double angle = ((i - (num_rays / 2)) * data->player.fov) / num_rays;
            angle_rad = angle * (PI / 180);
            distance = sqrt(pow(*ray_x - data->player.x, 2) + pow(*ray_y - data->player.y, 2)) * cos(angle_rad);

            // Vous pouvez supprimer la logique de texture ici pour le moment
            return distance;
        }

        // Si le rayon sort de la carte, on arrête aussi
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
		render_3d(data, data->player.distance, i);
    }
	//draw mini map + fov de la minimap
	draw_map(data);
	draw_fov(data);
}
