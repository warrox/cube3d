#include "../../includes/cub3D_lib.h"

int update_player_pos(t_data *data,int player_x,int player_y)
{
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

