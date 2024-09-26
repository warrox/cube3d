#include "../../includes/cub3D_lib.h"
#include <stdio.h>


int update_player_pos(t_data *data,int player_x,int player_y)
{
	data->player.size_width = data->cell_width * 0.25;
	data->player.size_height = data->cell_height * 0.25;
	// Utilise la position du joueur en pixels (déjà calculée en termes de grille dans key_handler)
	player_x = data->player.x * data->cell_width;
	player_y = data->player.y * data->cell_height;
	// Dessiner le joueur (après avoir dessiné la carte)
	// draw_rectangle(data, player_x, player_y, data->player.size_width,data->player.size_height, 0xFF0000);	
	ray_cast_radians(data);

	return(0);
}
void	draw_rectangle(t_data *data, int x, int y, int width, int height,
		int color)
{
	int	i;
	int	j;

	i = x;
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


int	close_window(int keycode, t_data *data)
{
	free_file_struct(data);
	exit(EXIT_SUCCESS);
	return(keycode);
}

// void compass(t_data *data)
// {
// 	printf("player : %f\n", data->player.angle);
// 	if(data->player.angle >= 1.38 && data->player.angle <= 2.6 )
// 		printf("South wall\n");
// 	if(data->player.angle <= 5.25 && data->player.angle >= 3.75 )
// 		printf("North wall\n");
// 	if(data->player.angle <= 5.25 && data->player.angle >= 3.75 )
// 		printf("East wall\n");
// 	if(data->player.angle <= 5.25 && data->player.angle >= 3.75 )
// 		printf("West wall\n");
//
//
//
// 	// south 1.5
// 	// north 4.75 
// 	// east 0.17
// 	// west 3.07
// }
int	key_handler(int keycode, t_data *data)
{
	
	if (keycode == W_KEY)
	{
		data->player.x += MOVE_SPEED * cos(data->player.angle);
		data->player.y += MOVE_SPEED * sin(data->player.angle);
	}
	else if (keycode == S_KEY)
	{
		data->player.x -= MOVE_SPEED * cos(data->player.angle);
		data->player.y -= MOVE_SPEED * sin(data->player.angle);
	}
	else if (keycode == ARROW_LEFT)
	{
		data->player.angle -= ROTATION_SPEED;
		if (data->player.angle < 0)
		{
			data->player.angle += 2 * M_PI;
		}
	}
	else if (keycode == ARROW_RIGHT)
	{
		data->player.angle += ROTATION_SPEED;
		if (data->player.angle > 2 * M_PI)
		{
			data->player.angle -= 2 * M_PI;
		}
	}
	if (keycode == A_KEY)
	{
		data->player.y += MOVE_SPEED * cos(data->player.angle);
		data->player.x += MOVE_SPEED * sin(data->player.angle);
	}
	if (keycode == D_KEY)
	{
		data->player.y -= MOVE_SPEED * cos(data->player.angle);
		data->player.x -= MOVE_SPEED * sin(data->player.angle);
	}
	if (keycode == ESCAPE)
	{
		free_file_struct(data);
		exit(EXIT_SUCCESS);
	}
	// Vérification des collisions (pour éviter que le joueur traverse les murs)
	// if (data->map_test[(int)data->player.y][(int)data->player.x] != '1')
	// {
	// 	data->player.x = data->player.x;			
	// 	data->player.y = data->player.y;
	// }
	return (0);
}


void draw_map(t_data *data)
{
	int i = 0;
	int j = 0;
	// Affichage de la mini-map (murs et sol)
	i = 0;
	while (i < data->file->line_map)
	{
		j = 0;
		while (j < data->file->max_len)
		{
			if (data->file->map[i][j] == '1')
			{
				draw_rectangle(data, j * data->cell_width, i
					* data->cell_height, data->cell_width, data->cell_height,
					0x808080); // mur gris
			}
			else
			{
				draw_rectangle(data, j * data->cell_width, i
					* data->cell_height, data->cell_width, data->cell_height,
					0xFFFFFF); // sol blanc
			}
			j++;
		}
		i++;
	}


}

