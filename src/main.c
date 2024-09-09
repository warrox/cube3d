/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:10:46 by whamdi            #+#    #+#             */
/*   Updated: 2024/09/09 11:32:37 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// REVOIR 4. Calcul de la Direction de Chaque Rayon
#include <stdio.h>
#include "../includes/cub3D_lib.h"
// implement a calculation function to build the fov
char map[MAP_HEIGHT][MAP_WIDTH + 1] = {
    "111111",
    "101001",
    "101001",
    "10E001",
    "111111"
};


#define ROTATION_SPEED 0.1 // Vitesse de rotation (en radians)

int key_handler(int keycode, t_data *data) 
{
    if (keycode == W_KEY) { // Avancer
        data->player.x += MOVE_SPEED * cos(data->player.angle);
        data->player.y += MOVE_SPEED * sin(data->player.angle);
    } 
    else if (keycode == S_KEY) { // Reculer
        data->player.x -= MOVE_SPEED * cos(data->player.angle);
        data->player.y -= MOVE_SPEED * sin(data->player.angle);
    } 
    else if (keycode == ARROW_LEFT) { // Rotation à gauche
        data->player.angle -= ROTATION_SPEED; 
        if (data->player.angle < 0) { // Gérer les angles négatifs
            data->player.angle += 2 * M_PI;
        }
    } 
    else if (keycode == ARROW_RIGHT) { // Rotation à droite
        data->player.angle += ROTATION_SPEED; 
        if (data->player.angle > 2 * M_PI) { // Gérer les angles supérieurs à 360°
            data->player.angle -= 2 * M_PI;
        }
    }
	if(keycode == A_KEY)
	{
		data->player.y += MOVE_SPEED * cos(data->player.angle);
        data->player.x += MOVE_SPEED * sin(data->player.angle);
		printf("GOIN]n");
	}
	if(keycode == D_KEY)
	{
		data->player.y -= MOVE_SPEED * cos(data->player.angle);
        data->player.x -= MOVE_SPEED * sin(data->player.angle);
		printf("GOIN]n");
	}
	if(keycode == ESCAPE)
	{
		exit(EXIT_SUCCESS);
	}


    // Vérification des collisions (pour éviter que le joueur traverse les murs)
    if (map[(int)data->player.y][(int)data->player.x] != '1') {
        data->player.x = data->player.x;
        data->player.y = data->player.y;
    }

    return (0);
}


int	ray_render(void *param)
{
	t_data *data = (t_data *) param;
    
    mlx_destroy_image(data->mlx.p_mlx, data->mlx.img);
	data->mlx.img = mlx_new_image(data->mlx.p_mlx, WIDTH, HEIGHT);
    data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
    
    ray_cast_radians(data); 
    mlx_put_image_to_window(data->mlx.p_mlx, data->mlx.mlx_win, data->mlx.img, 0, 0);

    return (0);
}

void draw_rectangle(t_data *data, int x, int y, int width, int height, int color)
{
	int i = x;
	int j;
	
	while (i < x + width)
	{
		j = y;
		while (j < y + height)
		{
			img_pix_put(data, i, j, color);
			j++;
		}
		i++;
	}
}

int minimap_render(void *param)
{
    t_data *data = (t_data *)param;
    int i = 0;
    int j;
    data->cell_width = WIDTH / MAP_WIDTH;
    data->cell_height = HEIGHT / MAP_HEIGHT;

    mlx_destroy_image(data->mlx.p_mlx, data->mlx.img);
    data->mlx.img = mlx_new_image(data->mlx.p_mlx, WIDTH, HEIGHT);
    data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);

    // Affichage de la mini-map (murs et sol)
    while (i < MAP_HEIGHT)
    {
        j = 0;
        while (j < MAP_WIDTH)
        {
            if (map[i][j] == '1')
            {
                draw_rectangle(data, j * data->cell_width, i * data->cell_height, data->cell_width, data->cell_height, 0x808080); // mur gris
            }
            else if (map[i][j] == '0' || map[i][j] == 'E')
            {
                draw_rectangle(data, j * data->cell_width, i * data->cell_height, data->cell_width, data->cell_height, 0xFFFFFF); // sol blanc
            }
            j++;
        }
        i++;
    }

    // Dessiner le joueur après la mini-map
	// faire nouvel fonction a partir d'ici
    data->player.size_width = data->cell_width * 0.25;
    data->player.size_height = data->cell_height * 0.25;

    // Utilise la position du joueur en pixels (déjà calculée en termes de grille dans key_handler)
    double player_x = data->player.x * data->cell_width;
    double player_y = data->player.y * data->cell_height;

    // Dessiner le joueur (après avoir dessiné la carte)
    draw_rectangle(data, player_x, player_y, data->player.size_width , data->player.size_height , 0xFF0000);
	ray_cast_radians(data);
    mlx_put_image_to_window(data->mlx.p_mlx, data->mlx.mlx_win, data->mlx.img, 0, 0);
    return (0);
}
int	init_mlx(t_data *data)
{
	data->mlx
		.mlx_win = NULL;
	data->mlx.img = NULL;
	data->mlx.addr = NULL;
	data->mlx.bits_per_pixel = 0;
	data->mlx.line_length = 0;
	data->mlx.endian = 0;

	data->mlx.p_mlx = mlx_init();
	if (data->mlx.p_mlx == NULL)
		return (1);
	data->mlx.mlx_win = mlx_new_window(data->mlx.p_mlx, WIDTH, HEIGHT, "Cube3d");
	if (data->mlx.mlx_win == NULL)
	{
		free(data->mlx.mlx_win);
		return (1);
	}
	data->mlx.img = mlx_new_image(data->mlx.p_mlx, WIDTH, HEIGHT);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bits_per_pixel,
			&data->mlx.line_length, &data->mlx.endian);	
	mlx_put_image_to_window(data->mlx.p_mlx, data->mlx.mlx_win, data->mlx.img, 0, 0);	
	return (0);
}

int main(int argc, char **argv, char **envp) 
{
    t_data data;
	checker(argc, argv, envp);
	map_parser(&data, argv[1]);	
	// carte vérification
    for (int i = 0; i < MAP_HEIGHT; i++) {
        printf("%s\n", map[i]);
    }
	init_player(&data); 

    // Rechercher la position initiale du joueur
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E') {
                data.player.x = j;
                data.player.y = i;
				data.player.angle = get_angle_posplayer(map[i][j]);
                data.player.dir = map[i][j];
                break;
            }
        }
    }
	printf("player x %f\t player y %f\n ", data.player.x, data.player.y);
	init_mlx(&data);
	mlx_hook(data.mlx.mlx_win, KeyPress, KeyPressMask, key_handler, &data);		
	// mlx_loop_hook(data.mlx.p_mlx, ray_render, (void *)&data);
	mlx_loop_hook(data.mlx.p_mlx, minimap_render, (void *)&data);	

	// mlx_hook(data.mlx.p_mlx, 17, 0, close_window, &data);
	mlx_loop(data.mlx.p_mlx);
}
