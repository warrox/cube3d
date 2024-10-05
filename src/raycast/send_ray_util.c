/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ray_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:46:16 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/05 14:54:01 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

static int	is_wall_hit(t_ray_context *ctx)
{
	int	map_x;
	int	map_y;

	map_x = ctx->calc->map_x;
	map_y = ctx->calc->map_y;
	return (map_x >= 0 && map_x < ctx->data->file->max_len && map_y >= 0
		&& map_y < ctx->data->file->line_map
		&& ctx->data->file->map[map_y][map_x] == '1');
}

static void	assign_texture_x(t_ray_context *ctx, t_texture **texture)
{
	if (ctx->calc->ray_dir_y > 0)
		*texture = &ctx->data->so;
	else
		*texture = &ctx->data->no;
	ctx->calc->hit_x = *(ctx->ray_x) - floor(*(ctx->ray_x));
}

static void	assign_texture_y(t_ray_context *ctx, t_texture **texture)
{
	if (ctx->calc->ray_dir_x > 0)
		*texture = &ctx->data->ea;
	else
		*texture = &ctx->data->we;
	ctx->calc->hit_x = *(ctx->ray_y) - floor(*(ctx->ray_y));
}

int	check_hit(t_ray_context *ctx, t_texture **texture)
{
	ctx->calc->map_x = (int)*(ctx->ray_x);
	ctx->calc->map_y = (int)*(ctx->ray_y);
	if (is_wall_hit(ctx))
	{
		ctx->calc->hit = 1;
		ctx->calc->x_dist = fabs(*(ctx->ray_x) - floor(*(ctx->ray_x) + 0.5));
		ctx->calc->y_dist = fabs(*(ctx->ray_y) - floor(*(ctx->ray_y) + 0.5));
		if (ctx->calc->x_dist > ctx->calc->y_dist)
			assign_texture_x(ctx, texture);
		else
			assign_texture_y(ctx, texture);
		return (1);
	}
	return (0);
}

double	calculate_distance(t_ray_context *ctx)
{
	double	corrected_angle;
	double	dx;
	double	dy;

	corrected_angle = ctx->ray_angle - ctx->data->player.angle;
	if (corrected_angle < -PI)
		corrected_angle += 2 * PI;
	if (corrected_angle > PI)
		corrected_angle -= 2 * PI;
	dx = *(ctx->ray_x) - ctx->data->player.x;
	dy = *(ctx->ray_y) - ctx->data->player.y;
	return (sqrt(dx * dx + dy * dy) * cos(corrected_angle));
}
