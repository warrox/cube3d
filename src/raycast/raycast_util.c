/*                                                        :::      ::::::::   */
/*   raycast_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:06:23 by whamdi            #+#    #+#             */
/*   Updated: 2024/09/25 10:59:18 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"
#include <stdio.h>

//WARNING: loadtext
void load_textures(t_data *data)
{
	data->wall_textures.no.img = mlx_xpm_file_to_image(data->mlx.p_mlx, data->file->path->path_no, &data->wall_textures.no.width, &data->wall_textures.no.height); 
 	data->wall_textures.no.addr = mlx_get_data_addr(data->wall_textures.no.img, &data->wall_textures.no.bpp, &data->wall_textures.no.line_length, &data->wall_textures.no.endian);

data->wall_textures.so.img = mlx_xpm_file_to_image(data->mlx.p_mlx, data->file->path->path_so, &data->wall_textures.so.width, &data->wall_textures.so.height);
data->wall_textures.so.addr = mlx_get_data_addr(data->wall_textures.so.img, &data->wall_textures.so.bpp, &data->wall_textures.so.line_length, &data->wall_textures.so.endian);

data->wall_textures.ea.img = mlx_xpm_file_to_image(data->mlx.p_mlx, data->file->path->path_ea, &data->wall_textures.ea.width, &data->wall_textures.ea.height);
data->wall_textures.ea.addr = mlx_get_data_addr(data->wall_textures.ea.img, &data->wall_textures.ea.bpp, &data->wall_textures.ea.line_length, &data->wall_textures.ea.endian);

data->wall_textures.we.img = mlx_xpm_file_to_image(data->mlx.p_mlx, data->file->path->path_we, &data->wall_textures.we.width, &data->wall_textures.we.height);
data->wall_textures.we.addr = mlx_get_data_addr(data->wall_textures.we.img, &data->wall_textures.we.bpp, &data->wall_textures.we.line_length, &data->wall_textures.we.endian);
}

void select_wall_texture(t_data *data, char wall_direction)
{
	if (wall_direction == 'N')  // Mur côté Nord
		data->current_texture = &data->wall_textures.no;
	else if (wall_direction == 'S')  // Mur côté Sud
		data->current_texture = &data->wall_textures.so;
	else if (wall_direction == 'W')  // Mur côté Ouest
		data->current_texture = &data->wall_textures.we;
	else if (wall_direction == 'E')  // Mur côté Est
		data->current_texture = &data->wall_textures.ea;
}
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

            if (map_x >= 0 && map_x < data->file->max_len && map_y >= 0 && map_y < data->file->line_map && data->file->map[map_y][map_x] == '1')
            {
                hit = 1;
            }

            if (map_x < 0 || map_x >=data->file->max_len  || map_y < 0 || map_y >= data->file->line_map)
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
char get_wall_direction(t_data *data,double ray_dir_x, double ray_dir_y)
{

    if (fabs(ray_dir_x) > fabs(ray_dir_y))
    {
        if (ray_dir_x > 0)
		{
			// printf("1\n");
			return RIGHT;   // Mur Est
		}
        else
		{
			
			// printf("2\n");
			return LEFT;    // Mur Ouest
		}
    }
    else  // Si Y 
    {
        if (ray_dir_y > 1)
		{
			
			// printf("3\n");
			return DOWN;    // Mur Sud
		}
        else
		{
			printf("4\n");	
			return UP;      // Mur Nord
		}
    }
	
	// printf("XX\n");
	return (data->file->orientation);
}

void draw_vertical_line(t_data *data, int x, int start, int end)
{
    int y;
    int texture_y;
    double tex_pos;
    double step;
	int wall_color;
    t_texture *texture = &data->upcoming_texture;

    // Vérifier que la colonne x est dans les limites de l'écran
    if (x < 0 || x >= WIDTH)
        return;

    if (!texture || !texture->addr)
    {
        printf("Texture or texture->addr is NULL\n");
        return;
    }

    // Calculer le pas (step) pour parcourir la texture verticalement
    step = (double)texture->height / (end - start);
    
    // Initialiser la position dans la texture
    tex_pos = 0;

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

    //HACK:WALL draw
	while (y <= end)
    {
        if (y >= 0 && y < HEIGHT)
        {
            // Calcul de la coordonnée Y de la texture
            texture_y = (int)tex_pos & (texture->height - 1);

            // Vérifier que texture_y est dans les limites
            if (texture_y < 0 || texture_y >= texture->height)
            {
                printf("texture_y is out of bounds: %d\n", texture_y);
                return;
            }

            // Incrémenter tex_pos pour le prochain pixel
            tex_pos += step;

            // Calculer la couleur du pixel de la texture
            wall_color = *(int *)(texture->addr + (texture_y * texture->line_length));

            // Appliquer la couleur sur la ligne de pixels du mur
            img_pix_put(data, x, y, wall_color);
        }
        y++;
    }

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
	// (void) data, (void) x; 
	draw_vertical_line(data,x ,draw_start, draw_end);
}


double send_ray(t_data *data, double ray_angle, double fov_radians, double *ray_x, double *ray_y, int i, int num_rays){

	
	t_texture texture; 
	double ray_dir_x;
    double ray_dir_y;
	int map_x; 
	int map_y; // Position dans la grille de la carte
	int hit; // Indicateur de collision
	int old_x = 0;
	int old_y = 0;
	int plane_dimension = WIDTH * HEIGHT;
	double subsequent_ray = 0;
	double distance = 0;
	double	angle_rad = 0; 
	// Direction du rayon (composantes x et y)
	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);

	// Initialisation des coordonnées du rayon (commence à la position du joueur)
	*ray_x = data->player.x;
	*ray_y = data->player.y;
	hit = 0;
	old_x = *ray_x;
	old_y = *ray_y;
	// Parcourir le rayon jusqu'à rencontrer un mur "1"
	while (!hit)
	{
		// Avancer le long du rayon
		*ray_x += ray_dir_x * 0.01; // 0.1 est un pas relativement petit pour plus de précision
		*ray_y += ray_dir_y * 0.01;
		old_x *= 0.01;
		old_y *= 0.01;
		// Convertir les coordonnées réelles en coordonnées de la carte (entier)
		map_x = (int)*ray_x;
		map_y = (int)*ray_y;
		subsequent_ray = fov_radians/ plane_dimension; // Angle between subsequent rays = 60/800 degrees
		// Vérifier si le rayon touche un mur
		//WARNING: wall direction 
		int direction = get_wall_direction(data, map_x, map_y);
		// printf("Ray_x : %f\t Ray_y : %f\n", map_x, map_y);
		if (direction == UP)
		{
			// printf("A\n");
			data->upcoming_texture = data->wall_textures.no;
		}
		else if (direction == DOWN)
		{	
			// printf("B\n");
			data->upcoming_texture = data->wall_textures.no;
			data->upcoming_texture = data->wall_textures.so;
		}
		else if (direction == LEFT)
		{
			
			// printf("C\n");
			data->upcoming_texture = data->wall_textures.no;
			data->upcoming_texture = data->wall_textures.we;
		}
		else if (direction == RIGHT)
		{
			
			// printf("D\n");
			texture = data->wall_textures.no;
			texture = data->wall_textures.ea;
		}

		if (map_x >= 0 && map_x < data->file->max_len && map_y >= 0 && map_y < data->file->line_map && data->file->map[map_y][map_x] == '1')
		{
			hit = 1;// Rayon a touché un mur
			//
			double angle = ((i - (num_rays / 2)) * data->player.fov) / num_rays;

			angle_rad = angle * (PI / 180);
			distance = (sqrt(pow(*ray_x - data->player.x, 2) + pow(*ray_y - data->player.y, 2)));
			return (distance * cos(angle_rad));	
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
	int player_pos[2];
    int num_rays = 1000; // Nombre de rayons à tracer pour couvrir le FOV
	
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
    player_pos[0] = data->player.x * data->cell_width;
    player_pos[1] = data->player.y * data->cell_height;
	
    while (i++ < num_rays)
    {	
		data->player.distance = send_ray(data, ray_angle, fov_radians, &ray_x, &ray_y, i, num_rays);
		ray_angle = data->player.angle - (fov_radians / 2) + (i * angle_step);
		render_3d(data, data->player.distance, i);
		
        // Calcul de la position finale du rayon en pixels (là où il a touché un mur ou est sorti de la carte)
        data->player.arrival_pos[0] = ray_x * data->cell_width;
        data->player.arrival_pos[1] = ray_y * data->cell_height;
		
        // Tracer la ligne (rayon) entre la position du joueur et la position d'arrêt
		data->player.map_pos[0] = player_pos[0];
		data->player.map_pos[1] = player_pos[1];

		data->player.arrival_pos[0] = data->player.arrival_pos[0];
		data->player.arrival_pos[1] = data->player.arrival_pos[1];
		// storage_box4render(map_x,map_y,data);
    }
	//draw mini map + fov de la minimap
	draw_map(data);
	draw_fov(data);
}
