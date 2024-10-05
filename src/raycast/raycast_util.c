/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:06:23 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/05 15:00:39 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

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
	data->player.fov = 60; // fov de 60 degres
	data->player.angle = 0;
	data->player.distance = 0;
	data->player.time = 0;    // time of current frame
	data->player.oldtime = 0; // time of previous frame
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

void	draw_vertical_line(t_data *data, int x, int start, int end,
		t_texture *texture, int wall_height, double hit_x)
{
	int		y;
	int		tex_y;
	double	step;
	double	texture_pos;
	int		tex_x;
	int		color;

	tex_x = (int)(hit_x * texture->width) % texture->width;
	y = -1;
	while (++y < start)
		img_pix_put(data, x, y, data->file->color->conv_c); // Couleur du ciel
	step = (double)texture->height / wall_height;
	texture_pos = (start - HEIGHT / 2 + wall_height / 2) * step;
	while (++y <= end)
	{
		tex_y = (int)texture_pos % texture->height;
		color = *(unsigned int *)(texture->addr + (tex_y * texture->line_lengh
					+ tex_x * (texture->bpp / 8)));
		img_pix_put(data, x, y, color);
		texture_pos += step;
	}
	while (y < HEIGHT)
	{
		img_pix_put(data, x, y, data->file->color->conv_f);
		y++;
	}
}

void	render_3d(t_data *data, double distance, int x, t_texture *texture,
		double hit_x)
{
	int	wall_height;
	int	draw_start;
	int	draw_end;

	if (distance <= 0)
		return ;
	wall_height = (int)(HEIGHT / distance);
	draw_start = -wall_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = wall_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	draw_vertical_line(data, x, draw_start, draw_end, texture, wall_height,
		hit_x);
}

double	send_ray(t_data *data, double ray_angle, double *ray_x, double *ray_y)
{
	t_calcul		c;
	t_texture		*texture;
	t_ray_context	ctx;

	ctx = {&c, data, ray_x, ray_y, ray_angle};
	init_send_ray(&ctx);
	while (!c.hit)
	{
		update_ray_position(&ctx);
		if (check_hit(&ctx, &texture))
		{
			c.distance = calculate_distance(&ctx);
			render_3d(data, c.distance, data->i, texture, c.hit_x);
			return (c.distance);
		}
		if (c.map_x < 0 || c.map_x >= data->file->max_len || c.map_y < 0
			|| c.map_y >= data->file->line_map)
			c.hit = 1;
	}
	return (0);
}

void	move_player(t_data *data)
{
	int	trigger;

	trigger = 0;
	if (data->file->map[(int)(data->player.y + (MOVE_SPEED
				* sin(data->player.angle)))][(int)(data->player.x + (MOVE_SPEED
				* cos(data->player.angle)))] == 'W'
		|| data->file->map[(int)(data->player.y - (MOVE_SPEED
				* sin(data->player.angle)))][(int)(data->player.x - (MOVE_SPEED
				* cos(data->player.angle)))] == 'W')
		trigger = 1;
	if (data->player.movey == 1 && (trigger == 1
			|| data->file->map[(int)(data->player.y + (MOVE_SPEED
					* sin(data->player.angle)))][(int)(data->player.x
				+ (MOVE_SPEED * cos(data->player.angle)))] == '0'))
	{
		data->player.x += MOVE_SPEED * cos(data->player.angle);
		data->player.y += MOVE_SPEED * sin(data->player.angle);
	}
	if (data->player.movey == -1 && (trigger == 1
			|| data->file->map[(int)(data->player.y - (MOVE_SPEED
					* sin(data->player.angle)))][(int)(data->player.x
				- (MOVE_SPEED * cos(data->player.angle)))] == '0'))
	{ // S
		data->player.x -= MOVE_SPEED * cos(data->player.angle);
		data->player.y -= MOVE_SPEED * sin(data->player.angle);
	}
	if (data->player.movex == 1 && (trigger == 1
			|| data->file->map[(int)(data->player.y + (MOVE_SPEED
					* cos(data->player.angle + PI / 2)))][(int)(data->player.x
				+ (MOVE_SPEED * sin(data->player.angle + PI / 2)))] == '0'))
	{
		data->player.x += MOVE_SPEED * cos(data->player.angle + PI / 2);
		data->player.y += MOVE_SPEED * sin(data->player.angle + PI / 2);
	}
	if (data->player.movex == -1 && (trigger == 1
			|| data->file->map[(int)(data->player.y - (MOVE_SPEED
					* cos(data->player.angle + PI / 2)))][(int)(data->player.x
				- (MOVE_SPEED * sin(data->player.angle + PI / 2)))] == '0'))
	{
		data->player.x -= MOVE_SPEED * cos(data->player.angle + PI / 2);
		data->player.y -= MOVE_SPEED * sin(data->player.angle + PI / 2);
	}
	trigger = 0;
}

void	ray_cast_radians(t_data *data)
{
	double	ray_angle;
	double	ray_x;
	double	ray_y;
	int		center_plane[2];
	double	angle_step;

	data->num_rays = 1000;
	center_plane[0] = WIDTH / 2;
	center_plane[1] = HEIGHT / 2;
	data->fov_radians = data->player.fov * (PI / 180.0);
	angle_step = data->fov_radians / data->num_rays;
	data->i = 0;
	while (data->i++ < data->num_rays)
	{
		ray_angle = data->player.angle - (data->fov_radians / 2) + (data->i
				* angle_step);
		data->player.distance = send_ray(data, ray_angle, &ray_x, &ray_y);
	}
	move_player(data);
	draw_map(data);
	draw_fov(data);
}
