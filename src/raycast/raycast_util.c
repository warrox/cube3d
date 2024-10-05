/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:06:23 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/05 14:27:13 by whamdi           ###   ########.fr       */
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
	{
		return (0);
	}
	if (player_dir == 'S')
	{
		return (PI / 2);
	}
	if (player_dir == 'N')
	{
		return (3 * PI / 2);
	}
	if (player_dir == 'W')
	{
		return (PI);
	}
	return (0);
}

void draw_vertical_line(t_data *data, int x, int start, int end, t_texture *texture, int wall_height, double hit_x)
{
    int y;
    int tex_y;
    double step;
    double texture_pos;
    int tex_x;
	int color;
	tex_x = (int)(hit_x * texture->width) % texture->width;
    y = -1;
    while (++y < start)
        img_pix_put(data, x, y, data->file->color->conv_c); // Couleur du ciel
    step = (double)texture->height / wall_height;
    texture_pos = (start - HEIGHT / 2 + wall_height / 2) * step;
    while (++y <= end)
    {
        tex_y = (int)texture_pos % texture->height;
        color = *(unsigned int *)(texture->addr + (tex_y * texture->line_lengh + tex_x * (texture->bpp / 8)));
        img_pix_put(data, x, y, color); // Dessiner le pixel du mur
        texture_pos += step;
    }

    while (y < HEIGHT)
    {
        img_pix_put(data, x, y, data->file->color->conv_f); // Couleur du sol
        y++;
    }
}

void render_3d(t_data *data, double distance, int x, t_texture *texture, double hit_x)
{
    int wall_height;
	int draw_start;
	int draw_end;

	if (distance <= 0)
        return;

    wall_height = (int)(HEIGHT / distance);
    draw_start = -wall_height / 2 + HEIGHT / 2;
    if (draw_start < 0) draw_start = 0;
    
    draw_end = wall_height / 2 + HEIGHT / 2;
    if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;

    draw_vertical_line(data, x, draw_start, draw_end, texture, wall_height, hit_x);
}
double send_ray(t_data *data, double ray_angle, double *ray_x, double *ray_y)
{
    
	t_calcul c;
	t_texture *texture;
	c.distance = 0;
    c.hit_x = 0;

    c.ray_dir_x = cos(ray_angle);
    c.ray_dir_y = sin(ray_angle);
    *ray_x = data->player.x;
    *ray_y = data->player.y;
    c.hit = 0;

    while (!c.hit)
    {
        *ray_x += c.ray_dir_x * 0.01;
        *ray_y += c.ray_dir_y * 0.01;

        c.map_x = (int)*ray_x;
        c.map_y = (int)*ray_y;

        if (c.map_x >= 0 && c.map_x < data->file->max_len && c.map_y >= 0 && c.map_y < data->file->line_map && data->file->map[c.map_y][c.map_x] == '1')
        {
            c.hit = 1;
            c.x_dist = fabs(*ray_x - floor(*ray_x + 0.5));
            c.y_dist = fabs(*ray_y - floor(*ray_y + 0.5));

            if (c.x_dist > c.y_dist)
            {
                if (c.ray_dir_y > 0)
                    texture = &data->so;
                else
                    texture = &data->no;
                c.hit_x = *ray_x - floor(*ray_x);
            }
            else
            {
                if (c.ray_dir_x > 0)
                    texture = &data->ea;
                else
                    texture = &data->we;
                c.hit_x = *ray_y - floor(*ray_y);
            }
            c.corrected_angle = ray_angle - data->player.angle;
            if (c.corrected_angle < -PI) c.corrected_angle += 2 * PI;
            if (c.corrected_angle > PI) c.corrected_angle -= 2 * PI;
            c.distance = sqrt(pow(*ray_x - data->player.x, 2) + pow(*ray_y - data->player.y, 2)) * cos(c.corrected_angle);
            render_3d(data, c.distance, data->i, texture, c.hit_x);
            return (c.distance);
        }

        if (c.map_x < 0 || c.map_x >= data->file->max_len || c.map_y < 0 || c.map_y >= data->file->line_map)
            c.hit = 1;
    }
    return (0);
}

void move_player(t_data *data)
{	
	int trigger;
	trigger = 0;
	
	if (data->file->map[(int)(data->player.y + (MOVE_SPEED * sin(data->player.angle)))][(int)(data->player.x + (MOVE_SPEED * cos(data->player.angle)))] == 'W' || 
	data->file->map[(int)(data->player.y - (MOVE_SPEED * sin(data->player.angle)))][(int)(data->player.x - (MOVE_SPEED * cos(data->player.angle)))] == 'W')
		trigger = 1;
	if (data->player.movey == 1 && (trigger == 1 ||  data->file->map[(int)(data->player.y + (MOVE_SPEED * sin(data->player.angle)))][(int)(data->player.x + (MOVE_SPEED * cos(data->player.angle)))] == '0'))
	{
		data->player.x += MOVE_SPEED * cos(data->player.angle );
		data->player.y += MOVE_SPEED * sin(data->player.angle);
	}
	if (data->player.movey == -1 && (trigger == 1 || data->file->map[(int)(data->player.y - (MOVE_SPEED * sin(data->player.angle)))][(int)(data->player.x - (MOVE_SPEED * cos(data->player.angle)))] == '0')){ //S
		data->player.x -= MOVE_SPEED * cos(data->player.angle);
		data->player.y -= MOVE_SPEED * sin(data->player.angle);
	}
	
	if (data->player.movex == 1 && (trigger == 1 || data->file->map[(int)(data->player.y + (MOVE_SPEED * cos(data->player.angle + PI / 2)))][(int)(data->player.x + (MOVE_SPEED * sin(data->player.angle + PI / 2)))] == '0'))
	{
		data->player.x += MOVE_SPEED * cos(data->player.angle + PI / 2);
		data->player.y += MOVE_SPEED * sin(data->player.angle + PI / 2);
	}

	if (data->player.movex == -1 && (trigger == 1 ||  data->file->map[(int)(data->player.y - (MOVE_SPEED * cos(data->player.angle + PI / 2)))][(int)(data->player.x - (MOVE_SPEED * sin(data->player.angle + PI / 2)))] == '0')) 
	{
		data->player.x -= MOVE_SPEED * cos(data->player.angle + PI / 2);
		data->player.y -= MOVE_SPEED * sin(data->player.angle + PI / 2);
	}
	trigger = 0;
}


void ray_cast_radians(t_data *data)
{
    double ray_angle;
    
	data->num_rays = 1000;
	
	double ray_x;
	double ray_y;

	int center_plane[2];
	center_plane[0] = WIDTH /2 ;
	center_plane[1] = HEIGHT /2;
	data->fov_radians = data->player.fov * (PI / 180.0);
    double angle_step = data->fov_radians / data->num_rays;
    	
	data->i = 0;
    while (data->i++ < data->num_rays)
    {
		ray_angle = data->player.angle - (data->fov_radians / 2) + (data->i * angle_step);
		data->player.distance = send_ray(data, ray_angle, &ray_x, &ray_y); 
    }
	move_player(data);
	draw_map(data);
	draw_fov(data);
}
