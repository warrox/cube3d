#include "../../includes/cub3D_lib.h"
int	minimap_render(void *param)
{

	t_data	*data;

	data = (t_data *)param;	
	// printf("string : %s\n", data->map_test[0]);
	data->cell_width = (WIDTH / 6) / data->file->max_len;
	data->cell_height = (HEIGHT / 6) / data->file->line_map;
	mlx_destroy_image(data->mlx.p_mlx, data->mlx.img);
	data->mlx.img = mlx_new_image(data->mlx.p_mlx, WIDTH, HEIGHT);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bits_per_pixel,
			&data->mlx.line_length, &data->mlx.endian);
	
	// Dessiner le joueur après la mini-map
	// faire nouvel fonction a partir d'ici
	mlx_put_image_to_window(data->mlx.p_mlx, data->mlx.mlx_win, data->mlx.img,
		0, 0);
	update_player_pos(data, data->player.x, data->player.y);
	return (0);
}

