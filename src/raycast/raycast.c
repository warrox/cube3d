/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 10:54:56 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/07 11:15:01 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int	minimap_render(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->cell_width = (WIDTH / 6) / data->file->max_len;
	data->cell_height = (HEIGHT / 6) / data->file->line_map;
	mlx_destroy_image(data->mlx.p_mlx, data->mlx.img);
	data->mlx.img = mlx_new_image(data->mlx.p_mlx, WIDTH, HEIGHT);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bits_per_pixel,
			&data->mlx.line_length, &data->mlx.endian);
	mlx_put_image_to_window(data->mlx.p_mlx, data->mlx.mlx_win, data->mlx.img,
		0, 0);
	update_player_pos(data, data->player.x, data->player.y);
	return (0);
}
