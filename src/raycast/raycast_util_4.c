/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:56:59 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/05 09:49:29 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int	key_handler(int keycode, t_data *data)
{
	if (keycode == ESCAPE)
	{
		free_resources(data);
		free_file_struct(data);
		exit(EXIT_SUCCESS);
	}
	process_angle(data, keycode);
	if (keycode == W_KEY)
		data->player.movey++;
	if (keycode == S_KEY)
		data->player.movey--;
	if (keycode == A_KEY)
		data->player.movex--;
	if (keycode == D_KEY)
		data->player.movex++;
	if (keycode == L_KEY)
	{
		data->lgbt_activated = 1;
		data->lgbt = !data->lgbt;
		render_rainbow_mode(data);
	}
	return (0);
}

int	key_release_handler(int keycode, t_data *data)
{
	if (keycode == W_KEY)
		data->player.movey--;
	else if (keycode == S_KEY)
		data->player.movey++;
	if (keycode == A_KEY)
		data->player.movex++;
	if (keycode == D_KEY)
		data->player.movex--;
	return (0);
}

void	draw_rectangle(t_data *data, int width, int height, int color)
{
	int	i;
	int	j;

	i = data->cell_wx;
	while (i < data->cell_wx + width)
	{
		j = data->cell_hy;
		while (j < data->cell_hy + height)
		{
			img_pix_put(data, i, j, color);
			j++;
		}
		i++;
	}
}

int	get_color_component(int color, int component, t_data *data)
{
	if (component == 0)
		return ((color >> 16) & 0xFF);
	else if (component == 1)
		return ((color >> 8) & 0xFF);
	else
		return (color & 0xFF);
}
