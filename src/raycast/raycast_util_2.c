/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:49:20 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/03 13:49:13 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "../../includes/cub3D_lib.h"

void draw_centered_text(t_data *data, char *text, int color)
{
	int i = 0;
	while (i++ < 900000)
		mlx_string_put(data->mlx.p_mlx, data->mlx.mlx_win, 400, 100, color, text);
}

void render_lgbt_mode(t_data *data)
{
	if (data->lgbt_activated)
		draw_centered_text(data, "LGBT MODE ACTIVATED", 0xFF00FF);
}

void free_images(t_data *data)
{
	if (data->no.img)
		mlx_destroy_image(data->mlx.p_mlx, data->no.img);
	if (data->so.img)
		mlx_destroy_image(data->mlx.p_mlx, data->so.img);
	if (data->ea.img)
		mlx_destroy_image(data->mlx.p_mlx, data->ea.img);
	if (data->we.img)
		mlx_destroy_image(data->mlx.p_mlx, data->we.img);
}

void free_resources(t_data *data)
{
	free_images(data);
	if (data->mlx.mlx_win)
		mlx_destroy_window(data->mlx.p_mlx, data->mlx.mlx_win);
	if (data->mlx.img)
		mlx_destroy_image(data->mlx.p_mlx, data->mlx.img);
	mlx_destroy_display(data->mlx.p_mlx);
	free(data->mlx.p_mlx);
}

void process_angle(t_data *data, int keycode)
{
	if (keycode == ARROW_LEFT)
		data->player.angle = fmod(data->player.angle - ROTATION_SPEED + 2 * M_PI, 2 * M_PI);
	else if (keycode == ARROW_RIGHT)
		data->player.angle = fmod(data->player.angle + ROTATION_SPEED, 2 * M_PI);
}

int key_handler(int keycode, t_data *data)
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
		render_lgbt_mode(data);
	}
	return (0);
}

int key_release_handler(int keycode, t_data *data)
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



int get_color_component(int color, int component)
{
	if (component == 0)
		return (color >> 16) & 0xFF;
	else if (component == 1)
		return (color >> 8) & 0xFF;
	else
		return color & 0xFF;
}

int interpolate_colors(int color1, int color2, double local_percentage)
{
	int r1 = get_color_component(color1, 0);
	int g1 = get_color_component(color1, 1);
	int b1 = get_color_component(color1, 2);
	
	int r2 = get_color_component(color2, 0);
	int g2 = get_color_component(color2, 1);
	int b2 = get_color_component(color2, 2);

	int r = (int)(r1 + local_percentage * (r2 - r1));
	int g = (int)(g1 + local_percentage * (g2 - g1));
	int b = (int)(b1 + local_percentage * (b2 - b1));

	return (r << 16 | g << 8 | b);
}

int lgbt_color(double percentage)
{
	int colors[6] = {0xFF0000, 0xFFA500, 0xFFFF00, 0x008000, 0x0000FF, 0x800080};
	int segment = (int)(percentage * 6);
	double local_percentage = (percentage * 6) - segment;

	if (segment >= 5)
		return colors[5];

	return interpolate_colors(colors[segment], colors[segment + 1], local_percentage);
}


void draw_cell(t_data *data, int x, int y, int color)
{
	draw_rectangle(data, x * data->cell_width, y * data->cell_height,
		data->cell_width, data->cell_height, color);
}

void draw_map(t_data *data)
{
	int i = 0;
	int j;
	double percentage;
	while (i < data->file->line_map)
	{
		j = 0;
		while (j < data->file->max_len)
		{
			if (data->file->map[i][j] == '1')
			{
				percentage = (double)(i * data->file->max_len + j) /
					(data->file->line_map * data->file->max_len);
				if(data->lgbt)
					draw_cell(data, j, i, lgbt_color(percentage));
				else
					draw_cell(data,j,i, 0x000000);
			}
			else
				draw_cell(data, j, i, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

int update_player_pos(t_data *data, int player_x, int player_y)
{
	ray_cast_radians(data);
	return (0);
}
