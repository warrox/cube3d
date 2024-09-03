/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:10:46 by whamdi            #+#    #+#             */
/*   Updated: 2024/09/03 15:42:26 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// REVOIR 4. Calcul de la Direction de Chaque Rayon
#include <stdio.h>
#include "../cube3d_lib.h"

void init_player(t_data *data)
{
	data->player.fov = 60; // fov de 60 degres
	data->player.angle = 0;
	data->player.distance = 0;
	data->wall = 0;
	data->ground = 0;
} 

// implement a calculation function to build the fov
void ray_cast_radians(int player_angle, t_data *data)
{
	int i = 0;
	double ray_angle;
	double ray_dir_x;
	double ray_dir_y;
	while(i < NUM_RAYS)
	{
		ray_angle = player_angle - (data->player.fov / 2) + (i * (data->player.fov / NUM_RAYS));
		ray_dir_x = cos(ray_angle);
		ray_dir_y = sin(ray_angle);
		i++;
	}
}
double get_angle_posplayer(char player_dir)
{
	if(player_dir == 'E')
	{
		return(0);
	}
	if(player_dir == 'N')
	{
		return(PI/2);
	}
	if(player_dir == 'S')
	{
		return(3 * PI / 2);
	}
	if(player_dir == 'W')
	{
		return(PI);
	}
	return(0);
}
char map[MAP_HEIGHT][MAP_WIDTH + 1] = {
    "111111",
    "100001",
    "10N001",
    "100001",
    "111111"
};

int main() {
    t_data data;
	// Afficher la carte pour vérification
    for (int i = 0; i < MAP_HEIGHT; i++) {
        printf("%s\n", map[i]);
    }
	// Initialisation du joueur
	init_player(&data); 
    int player_x = 0;
	int player_y = 0;
	int player_angle = 0;
    char player_dir = ' ';

    // Rechercher la position initiale du joueur
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E') {
                player_x = j;
                player_y = i;
				player_angle = get_angle_posplayer(map[i][j]);
                player_dir = map[i][j];
                map[i][j] = '0'; // Remplace la position par un espace vide une fois que tu as enregistré la position du joueur
                break;
            }
        }
    }
	// generate raycasting 
	ray_cast_radians(player_angle, &data);
	// de ce que je comprend je peux theroiquement deja afficher une scene en utilisant la minilibx
	/*Les etapes : 
	 * 1 - check de la map 
	 * 2 - chercher la position initiale du player via NWES
	 * 3 - obtenir l'angle du joueur
	 * 4 - cast les rayons en transformant l'angle en radians */
    printf("Player start position: (%d, %d)\n", player_x, player_y);
    printf("Player start direction: %c\n", player_dir);
    return 0;
}
