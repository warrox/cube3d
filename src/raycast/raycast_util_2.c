/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:49:20 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/03 15:15:24 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int	interpolate_colors(int color1, int color2, t_data *data)
{
	data->r1 = get_color_component(color1, 0, data);
	data->g1 = get_color_component(color1, 1, data);
	data->b1 = get_color_component(color1, 2, data);
	data->r2 = get_color_component(color2, 0, data);
	data->g2 = get_color_component(color2, 1, data);
	data->b2 = get_color_component(color2, 2, data);
	data->r = (int)(data->r1 + data->local_percentage * (data->r2 - data->r1));
	data->g = (int)(data->g1 + data->local_percentage * (data->g2 - data->g1));
	data->b = (int)(data->b1 + data->local_percentage * (data->b2 - data->b1));
	return (data->r << 16 | data->g << 8 | data->b);
}

int	lgbt_color(double percentage, t_data *data)
{
	int			segment;
	const int	colors[6] = {0xFF0000, 0xFFA500, 0xFFFF00, 0x008000, 0x0000FF,
		0x800080};

	segment = (int)(percentage * 6);
	data->local_percentage = (percentage * 6) - segment;
	if (segment >= 5)
		return (colors[5]);
	return (interpolate_colors(colors[segment], colors[segment + 1], data));
}

void	draw_cell(t_data *data, int x, int y, int color)
{
	data->cell_wx = x * data->cell_width;
	data->cell_hy = y * data->cell_height;
	draw_rectangle(data, data->cell_width, data->cell_height, color);
}

void	draw_map(t_data *data)
{
	int		i;
	int		j;
	double	percentage;

	i = 0;
	while (i < data->file->line_map)
	{
		j = 0;
		while (j < data->file->max_len)
		{
			if (data->file->map[i][j] == '1')
			{
				percentage = (double)(i * data->file->max_len + j)
					/ (data->file->line_map * data->file->max_len);
				if (data->lgbt)
					draw_cell(data, j, i, lgbt_color(percentage, data));
				else
					draw_cell(data, j, i, 0x000000);
			}
			else
				draw_cell(data, j, i, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

int	update_player_pos(t_data *data, int player_x, int player_y)
{
	ray_cast_radians(data);
	return (0);
}
