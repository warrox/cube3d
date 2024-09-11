#include "../../includes/cub3D_lib.h"


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
		{ // Gérer les angles négatifs
			data->player.angle += 2 * M_PI;
		}
	}
	else if (keycode == ARROW_RIGHT)
	{ // Rotation à droite
		data->player.angle += ROTATION_SPEED;
		if (data->player.angle > 2 * M_PI)
		{ // Gérer les angles supérieurs à 360°
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
	if (data->map_test[(int)data->player.y][(int)data->player.x] != '1')
	{
		data->player.x = data->player.x;			
		data->player.y = data->player.y;
	}
	return (0);
}

// void render_3d(t_data *data)
// {
// 	int ray_distance;
// 	int wall_height;
// 	int view_height;
// 	
//
// 	
//
// }

