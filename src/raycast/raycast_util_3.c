/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:56:12 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/03 14:56:15 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	draw_centered_text(t_data *data, char *text, int color)
{
	int	i;

	i = 0;
	while (i++ < 900000)
		mlx_string_put(data->mlx.p_mlx, data->mlx.mlx_win, 400, 100, color,
			text);
}

void	render_lgbt_mode(t_data *data)
{
	if (data->lgbt_activated)
		draw_centered_text(data, "LGBT MODE ACTIVATED", 0xFF00FF);
}

void	free_images(t_data *data)
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

void	free_resources(t_data *data)
{
	free_images(data);
	if (data->mlx.mlx_win)
		mlx_destroy_window(data->mlx.p_mlx, data->mlx.mlx_win);
	if (data->mlx.img)
		mlx_destroy_image(data->mlx.p_mlx, data->mlx.img);
	mlx_destroy_display(data->mlx.p_mlx);
	free(data->mlx.p_mlx);
}

void	process_angle(t_data *data, int keycode)
{
	if (keycode == ARROW_LEFT)
		data->player.angle = fmod(data->player.angle - ROTATION_SPEED + 2
				* M_PI, 2 * M_PI);
	else if (keycode == ARROW_RIGHT)
		data->player.angle = fmod(data->player.angle + ROTATION_SPEED, 2
				* M_PI);
}
