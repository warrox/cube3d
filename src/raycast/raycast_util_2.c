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
	// if (data->map_test[(int)data->player.y][(int)data->player.x] != '1')
	// {
	// 	data->player.x = data->player.x;			
	// 	data->player.y = data->player.y;
	// }
	return (0);
}


void render_3d(t_data *data)
{
    int wall_top;
    int wall_bottom;
    int wall_height;

    // Lancer un rayon pour chaque colonne de pixels à l'écran
    for (int ray_x = 0; ray_x < WIDTH; ray_x++)
    {
        // Calculer la hauteur du mur en fonction de la distance
        wall_height = (int)(64 / data->player.distance);

        // Calculer la position du haut et du bas du mur à dessiner
        wall_top = (HEIGHT / 2) - (wall_height / 2);
        if (wall_top < 0)
            wall_top = 0; // Éviter que le mur sorte de l'écran
        wall_bottom = (HEIGHT / 2) + (wall_height / 2);
        if (wall_bottom >= HEIGHT)
            wall_bottom = HEIGHT - 1; // Éviter que le mur sorte de l'écran

        // Dessiner le ciel (au-dessus du mur)
        for (int y = 0; y < wall_top; y++)
        {
            img_pix_put(data, ray_x, y, 0x2ea3d1); // Couleur du ciel
        }

        // Dessiner le mur pour cette colonne
        for (int y = wall_top; y <= wall_bottom; y++)
        {
            img_pix_put(data, ray_x, y, 0xFF0000); // Couleur du mur
        }

        // Dessiner le sol (en dessous du mur)
        for (int y = wall_bottom + 1; y < HEIGHT; y++)
        {
            img_pix_put(data, ray_x, y, 0x42423A); // Couleur du sol
        }
    }
	int i = 0;
	int j = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			if (data->map_test[i][j] == '1')
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
