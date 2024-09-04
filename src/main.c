/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:10:46 by whamdi            #+#    #+#             */
/*   Updated: 2024/09/04 13:38:43 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// REVOIR 4. Calcul de la Direction de Chaque Rayon
#include <stdio.h>
#include "../includes/cub3D_lib.h"

// implement a calculation function to build the fov
char map[MAP_HEIGHT][MAP_WIDTH + 1] = {
    "111111",
    "100001",
    "10N001",
    "100001",
    "111111"
};
/*void	*p_mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
*/
int	init_mlx(t_data *data)
{
	data->mlx.mlx_win = NULL;
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
	return (0);
}
int main(int argc, char **argv, char **envp) 
{
    t_data data;
	checker(argc, argv, envp);
	map_parser(&data, argv[1]);	
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
	init_mlx(&data);
	mlx_put_image_to_window(data.mlx.p_mlx, data.mlx.mlx_win, data.mlx.img, 0, 0);
	free_map_struct(&data);
    return 0;
}
