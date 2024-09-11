/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:06:23 by whamdi            #+#    #+#             */
/*   Updated: 2024/09/11 14:58:09 by whamdi           ###   ########.fr       */
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
	// data->wall = 0;
	// data->ground = 0;
	data->player.time = 0;    // time of current frame
	data->player.oldTime = 0; // time of previous frame
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


void draw_vector(t_data *data, int pos1[2], int pos2[2], int color)
{
    int x0 = pos1[0]; // Coordonnée x du point 1
    int y0 = pos1[1]; // Coordonnée y du point 1
    int x1 = pos2[0]; // Coordonnée x du point 2
    int y1 = pos2[1]; // Coordonnée y du point 2

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;
    int e2;

    while (1)
    {
        img_pix_put(data, x0, y0, color); // Dessine un pixel en blanc (ou autre couleur)

        if (x0 == x1 && y0 == y1) // Si la ligne est complète
            break;

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
}

void storage_box4render(int map_x, int map_y, t_data *data)
{
    double pos_x;
    double pos_y;
    double distance; // Utilisation d'un double pour la précision

    printf("player_x : %f\n", data->player.x);
    printf("player_y : %f\n", data->player.y);
	pos_x = data->player.x; // Position du joueur en x
    pos_y = data->player.y; // Position du joueur en y

    // Calcul de la distance euclidienne entre le joueur et le hit du rayon
    distance = sqrt(pow(map_x - pos_x, 2) + pow(map_y - pos_y, 2));
    
    data->player.distance = distance; // Stocker la distance

    printf("Player distance : %f\n", data->player.distance);
}
void ray_cast_radians(t_data *data)
{
    double ray_angle;
    double ray_dir_x;
    double ray_dir_y;
    int player_pos[2];
    int arrival_pos[2];
    int num_rays = 100; // Nombre de rayons à tracer pour couvrir le FOV
    double fov_radians = data->player.fov * (PI / 180.0); // Conversion du FOV en radians
    double angle_step = fov_radians / num_rays; // Pas d'angle entre chaque rayon
    double ray_x, ray_y; // Position temporaire du rayon
    int map_x, map_y; // Position dans la grille de la carte
    int hit; // Indicateur de collision
	int old_x = 0;
	int old_y = 0;
    player_pos[0] = data->player.x * data->cell_width;
    player_pos[1] = data->player.y * data->cell_height;

    for (int i = 0; i < num_rays; i++)
    {
        // Calcul de l'angle du rayon actuel
        ray_angle = data->player.angle - (fov_radians / 2) + (i * angle_step);
        
        // Direction du rayon (composantes x et y)
        ray_dir_x = cos(ray_angle);
        ray_dir_y = sin(ray_angle);

        // Initialisation des coordonnées du rayon (commence à la position du joueur)
        ray_x = data->player.x;
        ray_y = data->player.y;
        hit = 0;
		old_x = ray_x;
		old_y = ray_y;
        // Parcourir le rayon jusqu'à rencontrer un mur (cellule "1")
        while (!hit)
        {
            // Avancer le long du rayon
            ray_x += ray_dir_x * 0.1; // 0.1 est un pas relativement petit pour plus de précision
            ray_y += ray_dir_y * 0.1;
			old_x *= 0.1;
			old_y *= 0.1;
            // Convertir les coordonnées réelles en coordonnées de la carte (entier)
            map_x = (int)ray_x;
            map_y = (int)ray_y;

            // Vérifier si le rayon touche un mur
			if (map_x >= 0 && map_x < MAP_WIDTH && map_y >= 0 && map_y < MAP_HEIGHT && data->map_test[map_y][map_x] == '1')
            {
				hit = 1;// Rayon a touché un mur
				// render_3d(data);
				if(old_x >= MAP_WIDTH - 0.2 && old_y >= MAP_HEIGHT - 0.2)
				{
					printf("OKIDOKI\n"); //ESSAIE DE DETECTER UNE COLISION DU PLAYER PAR UN MUR MAIS MARCHE PAS CHECK IF AU DESSUS AVEC OLD X ET OLD Y
				}
            }

            // Si le rayon sort de la carte, on arrête aussi
            if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
            {
                hit = 1;
            }
        }

        // Calcul de la position finale du rayon en pixels (là où il a touché un mur ou est sorti de la carte)
        arrival_pos[0] = ray_x * data->cell_width;
        arrival_pos[1] = ray_y * data->cell_height;

        // Tracer la ligne (rayon) entre la position du joueur et la position d'arrêt
		storage_box4render(map_x,map_y,data);
    	draw_vector(data, player_pos, arrival_pos, 0xFF0000);
		render_3d(data);
    }
}
