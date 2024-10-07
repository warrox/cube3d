/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:05:43 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/07 11:31:39 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

static void	move_forward(t_data *data, int trigger)
{
	double	next_x;
	double	next_y;

	next_x = data->player.x + (MOVE_SPEED + COLLISION_BUFFER)
		* cos(data->player.angle);
	next_y = data->player.y + (MOVE_SPEED + COLLISION_BUFFER)
		* sin(data->player.angle);
	if (data->player.movey == 1 && (trigger == 1
			|| data->file->map[(int)(next_y)][(int)(next_x)] != '1'))
	{
		data->player.x += MOVE_SPEED * cos(data->player.angle);
		data->player.y += MOVE_SPEED * sin(data->player.angle);
	}
}

static void	move_backward(t_data *data, int trigger)
{
	double	next_x;
	double	next_y;

	next_x = data->player.x - (MOVE_SPEED + COLLISION_BUFFER)
		* cos(data->player.angle);
	next_y = data->player.y - (MOVE_SPEED + COLLISION_BUFFER)
		* sin(data->player.angle);
	if (data->player.movey == -1 && (trigger == 1
			|| data->file->map[(int)(next_y)][(int)(next_x)] != '1'))
	{
		data->player.x -= MOVE_SPEED * cos(data->player.angle);
		data->player.y -= MOVE_SPEED * sin(data->player.angle);
	}
}

static void	move_left(t_data *data, int trigger)
{
	double	next_x;
	double	next_y;

	next_x = data->player.x - (MOVE_SPEED + COLLISION_BUFFER)
		* cos(data->player.angle + PI / 2);
	next_y = data->player.y - (MOVE_SPEED + COLLISION_BUFFER)
		* sin(data->player.angle + PI / 2);
	if (data->player.movex == -1 && (trigger == 1
			|| data->file->map[(int)(next_y)][(int)(next_x)] != '1'))
	{
		data->player.x -= MOVE_SPEED * cos(data->player.angle + PI / 2);
		data->player.y -= MOVE_SPEED * sin(data->player.angle + PI / 2);
	}
}

static void	move_right(t_data *data, int trigger)
{
	double	next_x;
	double	next_y;

	next_x = data->player.x + (MOVE_SPEED + COLLISION_BUFFER)
		* cos(data->player.angle + PI / 2);
	next_y = data->player.y + (MOVE_SPEED + COLLISION_BUFFER)
		* sin(data->player.angle + PI / 2);
	if (data->player.movex == 1 && (trigger == 1
			|| data->file->map[(int)(next_y)][(int)(next_x)] != '1'))
	{
		data->player.x += MOVE_SPEED * cos(data->player.angle + PI / 2);
		data->player.y += MOVE_SPEED * sin(data->player.angle + PI / 2);
	}
}

void	move_player(t_data *data)
{
	int	trigger;

	trigger = 0;
	if (data->file->map[(int)(data->player.y + (MOVE_SPEED
				* sin(data->player.angle)))][(int)(data->player.x + (MOVE_SPEED
				* cos(data->player.angle)))] == '1'
		|| data->file->map[(int)(data->player.y - (MOVE_SPEED
				* sin(data->player.angle)))][(int)(data->player.x - (MOVE_SPEED
				* cos(data->player.angle)))] == '1')
		trigger = 1;
	move_forward(data, trigger);
	move_backward(data, trigger);
	move_left(data, trigger);
	move_right(data, trigger);
}
