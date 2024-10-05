/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ray_util_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:51:23 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/05 15:39:19 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	init_send_ray(t_ray_context *ctx)
{
	ctx->calc->distance = 0;
	ctx->calc->hit_x = 0;
	ctx->calc->ray_dir_x = cos(ctx->ray_angle);
	ctx->calc->ray_dir_y = sin(ctx->ray_angle);
	*(ctx->ray_x) = ctx->data->player.x;
	*(ctx->ray_y) = ctx->data->player.y;
	ctx->calc->hit = 0;
}

void	update_ray_position(t_ray_context *ctx)
{
	*(ctx->ray_x) += ctx->calc->ray_dir_x * 0.01;
	*(ctx->ray_y) += ctx->calc->ray_dir_y * 0.01;
}

void	img_pix_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 1 || x >= WIDTH - 1 || y < 1 || y >= HEIGHT - 1)
		return ;
	dst = data->mlx.addr + (y * data->mlx.line_length + x
			* (data->mlx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_player(t_data *data)
{
	data->player.fov = 60;
	data->player.angle = 0;
	data->player.distance = 0;
	data->player.time = 0;
	data->player.oldtime = 0;
	data->player.x = -1;
	data->player.y = -1;
	data->player.movex = 0;
	data->player.movey = 0;
	data->lgbt = 0;
}

double	get_angle_posplayer(char player_dir)
{
	if (player_dir == 'E')
		return (0);
	if (player_dir == 'S')
		return (PI / 2);
	if (player_dir == 'N')
		return (3 * PI / 2);
	if (player_dir == 'W')
		return (PI);
	return (0);
}
