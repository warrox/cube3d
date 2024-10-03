/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:49:20 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/03 12:57:00 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"


void	draw_centered_text(t_data *data, char *text, int color)
{
	int i = 0;
	while(i++ < 900000)
		mlx_string_put(data->mlx.p_mlx, data->mlx.mlx_win,400,100,color, text);
}

void render_lgbt_mode(t_data *data)
{
	if (data->lgbt_activated)
	{
		draw_centered_text(data, "LGBT MODE ACTIVATED", 0xFF00FF);	
	}
}

void free_resources(t_data *data)
{
    printf("A\n");
	if (data->no.img)
        mlx_destroy_image(data->mlx.p_mlx, data->no.img);
    if (data->so.img)
        mlx_destroy_image(data->mlx.p_mlx, data->so.img);
    if (data->ea.img)
        mlx_destroy_image(data->mlx.p_mlx, data->ea.img);
    if (data->we.img)
        mlx_destroy_image(data->mlx.p_mlx, data->we.img);
	    
    if (data->mlx.mlx_win)
        mlx_destroy_window(data->mlx.p_mlx, data->mlx.mlx_win);
    if (data->mlx.img)
        mlx_destroy_image(data->mlx.p_mlx, data->mlx.img);
	mlx_destroy_display(data->mlx.p_mlx);
	free(data->mlx.p_mlx);
    printf("b\n");
}

int key_handler(int keycode, t_data *data)
{
	if (keycode == W_KEY)
		data->player.movey++;
	else if (keycode == S_KEY)
		data->player.movey--;
	else if (keycode == ARROW_LEFT)
	{
		data->player.angle -= ROTATION_SPEED;
		if (data->player.angle < 0)
			data->player.angle += 2 * M_PI;
	}
	else if (keycode == ARROW_RIGHT)
	{
		data->player.angle += ROTATION_SPEED;
		if (data->player.angle > 2 * M_PI)
			data->player.angle -= 2 * M_PI;
	}
	if (keycode == A_KEY)
		data->player.movex--;
	if (keycode == D_KEY)
		data->player.movex++;
	if (keycode == ESCAPE)
	{
		free_resources(data);
		free_file_struct(data);
		exit(EXIT_SUCCESS);
	}
	if (keycode == L_KEY)
	{
		data->lgbt_activated = 1; // Désactive "LGBT MODE" quand on appuie sur L
		render_lgbt_mode(data);	
		data->lgbt = !data->lgbt; // Active/désactive le mode LGBT
	}
	return (0);
}

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


int lgbt_color(double percentage)
{
    int colors[6] = {0xFF0000, 0xFFA500, 0xFFFF00, 0x008000, 0x0000FF, 0x800080};
    int segment = (int)(percentage * 6);
    double local_percentage = (percentage * 6) - segment;

    if (segment >= 5)
        return colors[5];

    int r1 = (colors[segment] >> 16) & 0xFF;
    int g1 = (colors[segment] >> 8) & 0xFF;
    int b1 = colors[segment] & 0xFF;

    int r2 = (colors[segment + 1] >> 16) & 0xFF;
    int g2 = (colors[segment + 1] >> 8) & 0xFF;
    int b2 = colors[segment + 1] & 0xFF;

    int r = (int)(r1 + local_percentage * (r2 - r1));
    int g = (int)(g1 + local_percentage * (g2 - g1));
    int b = (int)(b1 + local_percentage * (b2 - b1));

    return (r << 16 | g << 8 | b);
}
void draw_map(t_data *data)
{
	int i = 0;
	int j = 0;
	double percentage;

	while (i < data->file->line_map)
	{
		j = 0;
		while (j < data->file->max_len)
		{
			if (data->file->map[i][j] == '1' && data->lgbt)
			{
				// mur lgbt :D 
				percentage = (double)(i * data->file->max_len + j) / (data->file->line_map * data->file->max_len);
				
				draw_rectangle(data, j * data->cell_width, i * data->cell_height, 
					data->cell_width, data->cell_height, lgbt_color(percentage));
			}
			else if(data->file->map[i][j] == '1' && data->lgbt == 0)
			{
				draw_rectangle(data, j * data->cell_width, i * data->cell_height, 
					data->cell_width, data->cell_height, 0000);

			}
			else
			{
				draw_rectangle(data, j * data->cell_width, i * data->cell_height, 
					data->cell_width, data->cell_height, 0xFFFFFF); // sol blanc
			}
			j++;
		}
		i++;
	}
}

