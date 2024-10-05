/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertical_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:09:42 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/05 15:10:20 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3D_lib.h"

static void	draw_sky(t_data *data, int x, int start)
{
	int y = -1;
	while (++y < start)
		img_pix_put(data, x, y, data->file->color->conv_c);
}

static void	draw_wall(t_data *data, int x, int start, int end, t_texture *texture, int wall_height, double hit_x)
{
	int		y;
	double	step = (double)texture->height / wall_height;
	double	texture_pos = (start - HEIGHT / 2 + wall_height / 2) * step;
	int		tex_x = (int)(hit_x * texture->width) % texture->width;
	int		tex_y;
	int		color;

	y = start - 1;
	while (++y <= end)
	{
		tex_y = (int)texture_pos % texture->height;
		color = *(unsigned int *)(texture->addr + (tex_y * texture->line_lengh
					+ tex_x * (texture->bpp / 8)));
		img_pix_put(data, x, y, color);
		texture_pos += step;
	}
}

static void	draw_floor(t_data *data, int x, int end)
{
	int y = end + 1;
	while (y < HEIGHT)
	{
		img_pix_put(data, x, y, data->file->color->conv_f);
		y++;
	}
}

void	draw_vertical_line(t_data *data, int x, int start, int end,
		t_texture *texture, int wall_height, double hit_x)
{
	draw_sky(data, x, start);
	draw_wall(data, x, start, end, texture, wall_height, hit_x);
	draw_floor(data, x, end);
}
