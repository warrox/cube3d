/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ray_util_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:51:23 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/05 14:53:40 by whamdi           ###   ########.fr       */
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
