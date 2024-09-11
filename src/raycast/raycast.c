#include "../../includes/cub3D_lib.h"
int	minimap_render(void *param)
{

	t_data	*data;
	int		i;
	int		j;

	data = (t_data *)param;	
	// printf("string : %s\n", data->map_test[0]);
	i = 0;
	data->cell_width = (WIDTH / 6) / MAP_WIDTH;
	data->cell_height = (HEIGHT / 6) / MAP_HEIGHT;
	mlx_destroy_image(data->mlx.p_mlx, data->mlx.img);
	data->mlx.img = mlx_new_image(data->mlx.p_mlx, WIDTH, HEIGHT);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bits_per_pixel,
			&data->mlx.line_length, &data->mlx.endian);
	// Affichage de la mini-map (murs et sol)
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
	update_player_pos(data, data->player.x, data->player.y);
	// Dessiner le joueur après la mini-map
	// faire nouvel fonction a partir d'ici
	mlx_put_image_to_window(data->mlx.p_mlx, data->mlx.mlx_win, data->mlx.img,
		0, 0);
	return (0);
}

