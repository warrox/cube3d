/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:50:38 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/05 15:50:44 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

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
	data->mlx.mlx_win = mlx_new_window(data->mlx.p_mlx, WIDTH, HEIGHT,
			"Cube3d");
	if (data->mlx.mlx_win == NULL)
	{
		free(data->mlx.mlx_win);
		return (1);
	}
	data->mlx.img = mlx_new_image(data->mlx.p_mlx, WIDTH, HEIGHT);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bits_per_pixel,
			&data->mlx.line_length, &data->mlx.endian);
	mlx_put_image_to_window(data->mlx.p_mlx, data->mlx.mlx_win, data->mlx.img,
		0, 0);
	return (0);
}
