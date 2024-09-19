/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:06:23 by whamdi            #+#    #+#             */
/*   Updated: 2024/09/19 15:04:11 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void draw_fov(t_data *data)
{
    double fov = 60 * (PI / 180.0);
    double half_fov = fov / 2;  
    int num_rays = 100; 
    double angle_step = fov / num_rays; 
    double ray_angle, ray_dir_x, ray_dir_y;
    double ray_x, ray_y;
    int hit, map_x, map_y;

    // Position du joueur sur la mini-map
    int player_pos[2];
    player_pos[0] = data->player.x * data->cell_width;
    player_pos[1] = data->player.y * data->cell_height;

    for (int i = 0; i < num_rays; i++)
    {
        ray_angle = data->player.angle - half_fov + (i * angle_step);

        ray_dir_x = cos(ray_angle);
        ray_dir_y = sin(ray_angle);

        ray_x = data->player.x;
        ray_y = data->player.y;
        hit = 0;

        while (!hit)
        {
            ray_x += ray_dir_x * 0.1;
            ray_y += ray_dir_y * 0.1;

            map_x = (int)ray_x;
            map_y = (int)ray_y;

            if (map_x >= 0 && map_x < MAP_WIDTH && map_y >= 0 && map_y < MAP_HEIGHT && data->map_test[map_y][map_x] == '1')
            {
                hit = 1;
            }

            if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
            {
                hit = 1;
            }
        }

        int arrival_pos[2];
        arrival_pos[0] = ray_x * data->cell_width;
        arrival_pos[1] = ray_y * data->cell_height;

        draw_vector(data, player_pos, arrival_pos, 0xFF0000);
    }
}
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
		img_pix_put(data, x0, y0, color);
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
    double distance;

    // printf("player_x : %f\n", data->player.x);
    // printf("player_y : %f\n", data->player.y);
	pos_x = data->player.x; // Position du joueur en x
    pos_y = data->player.y; // Position du joueur en y

    // Calcul de la distance entre le joueur et le hit du rayon
    distance = sqrt(pow(map_x - pos_x, 2) + pow(map_y - pos_y, 2));
    
    data->player.distance = distance; // Stocker la distance

    // printf("Player distance : %f\n", data->player.distance);
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
            img_pix_put(data, x, y, 0x87CEEB); // Couleur du ciel (bleu clair)
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
            img_pix_put(data, x, y, 0x8B4513); // Couleur du sol (marron)
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
    
	draw_vertical_line(data,x ,draw_start, draw_end, 0xff1241);
}
void ray_cast_radians(t_data *data)
{
    double ray_angle;
    
	double ray_dir_x;
    double ray_dir_y;
    
	int player_pos[2];
    int arrival_pos[2];
    int num_rays = 1000; // Nombre de rayons à tracer pour couvrir le FOV
	
	// **New var ** //
	int plane_dimension = WIDTH * HEIGHT;
	double distance;
	int center_plane[2];
	center_plane[0] = WIDTH /2 ;
	center_plane[1] = HEIGHT /2;
	// ** //
	double fov_radians = data->player.fov * (PI / 180.0); // Conversion du FOV en radians
    double angle_step = fov_radians / num_rays; // Pas d'angle entre chaque rayon
    
	double ray_x; 
	double ray_y; // Position temporaire du rayon
    
	int map_x; 
	int map_y; // Position dans la grille de la carte
    
	int hit; // Indicateur de collision
	
	int old_x = 0;
	int old_y = 0;
	int x = 0;	
	int i = 0;
	double subsequent_ray = 0;
    player_pos[0] = data->player.x * data->cell_width;
    player_pos[1] = data->player.y * data->cell_height;

    while (i++ < num_rays)
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
        // Parcourir le rayon jusqu'à rencontrer un mur "1"
        while (!hit)
        {
            // Avancer le long du rayon
            ray_x += ray_dir_x * 0.01; // 0.1 est un pas relativement petit pour plus de précision
            ray_y += ray_dir_y * 0.01;
			old_x *= 0.01;
			old_y *= 0.01;
            // Convertir les coordonnées réelles en coordonnées de la carte (entier)
            map_x = (int)ray_x;
            map_y = (int)ray_y;

			subsequent_ray = fov_radians/ plane_dimension; // Angle between subsequent rays = 60/800 degrees
            // Vérifier si le rayon touche un mur
			if (map_x >= 0 && map_x < MAP_WIDTH && map_y >= 0 && map_y < MAP_HEIGHT && data->map_test[map_y][map_x] == '1')
            {
				hit = 1;// Rayon a touché un mur
				distance = sqrt(pow(ray_x - data->player.x, 2) + pow(ray_y - data->player.y, 2));
				// printf("Distance : %f\n",distance);
				
				x = (int)((i / (double)num_rays) * WIDTH); // i est l'index du rayon
				render_3d(data, distance, x);
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
		data->player.map_pos[0] = player_pos[0];
		data->player.map_pos[1] = player_pos[1];

		data->player.arrival_pos[0] = arrival_pos[0];
		data->player.arrival_pos[1] = arrival_pos[1];
		storage_box4render(map_x,map_y,data);
		prespective_fn(data);
    }
	//draw mini map + fov de la minimap
	draw_map(data);
	draw_fov(data);
}
