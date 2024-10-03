/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:06:23 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/03 08:36:48 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"


void img_pix_put(t_data *data, int x, int y, int color)
{
    char *dst;

    if (x < 1 || x >= WIDTH - 1 || y < 1 || y >= HEIGHT - 1)
        return;
    dst = data->mlx.addr + (y * data->mlx.line_length + x * (data->mlx.bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}


void init_player(t_data *data)
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
}


double get_angle_posplayer(char player_dir)
{
    if (player_dir == 'E')
        return 0;
    if (player_dir == 'S')
        return PI / 2;
    if (player_dir == 'N')
        return 3 * PI / 2;
    if (player_dir == 'W')
        return PI;
    return 0;
}


void draw_sky_and_floor(t_data *data, int x, int start, int end)
{
    int y = 0;
    
    while (y < start)
        img_pix_put(data, x, y++, data->file->color->conv_c);
    while (y < HEIGHT)
        img_pix_put(data, x, y++, data->file->color->conv_f);
}


void draw_wall(t_data *data, int x, int start, int end, t_texture *texture, double hit_x)
{
    double texture_pos = (start - HEIGHT / 2 + (end - start) / 2) * ((double)texture->height / (end - start));
    int tex_x = (int)(hit_x * texture->width) % texture->width;
    int y = start;

    while (y <= end)
    {
        int tex_y = (int)texture_pos % texture->height;
        int color = *(unsigned int *)(texture->addr + (tex_y * texture->line_lengh + tex_x * (texture->bpp / 8)));
        img_pix_put(data, x, y++, color);
        texture_pos += (double)texture->height / (end - start);
    }
}


void render_3d(t_data *data, double distance, int x, t_texture *texture, double hit_x)
{
    if (distance <= 0)
        return;

    int wall_height = (int)(HEIGHT / distance);
    int draw_start = -wall_height / 2 + HEIGHT / 2;
    int draw_end = wall_height / 2 + HEIGHT / 2;

    draw_start = draw_start < 0 ? 0 : draw_start;
    draw_end = draw_end >= HEIGHT ? HEIGHT - 1 : draw_end;

    draw_sky_and_floor(data, x, draw_start, draw_end);
    draw_wall(data, x, draw_start, draw_end, texture, hit_x);
}


t_texture *select_texture(t_data *data, double ray_dir_x, double ray_dir_y, double *hit_x, double ray_x, double ray_y)
{
    double x_dist = fabs(ray_x - floor(ray_x + 0.5));
    double y_dist = fabs(ray_y - floor(ray_y + 0.5));

    if (x_dist > y_dist)
    {
        *hit_x = ray_x - floor(ray_x);
        return ray_dir_y > 0 ? &data->so : &data->no;
    }
    *hit_x = ray_y - floor(ray_y);
    return ray_dir_x > 0 ? &data->ea : &data->we;
}

double calculate_corrected_distance(t_data *data, double ray_angle, double ray_x, double ray_y)
{
    double corrected_angle = ray_angle - data->player.angle;
    corrected_angle = corrected_angle < -PI ? corrected_angle + 2 * PI : corrected_angle;
    corrected_angle = corrected_angle > PI ? corrected_angle - 2 * PI : corrected_angle;

    return sqrt(pow(ray_x - data->player.x, 2) + pow(ray_y - data->player.y, 2)) * cos(corrected_angle);
}


void init_send_ray_fn(t_ray_box *sr, t_data *data, double ray_angle)
{
    sr->ray_x = data->player.x;
    sr->ray_y = data->player.y;

    // Assign ray_dir_x and ray_dir_y in this function
    sr->ray_dir_x = cos(ray_angle);
    sr->ray_dir_y = sin(ray_angle);
}


double send_ray(t_data *data, double ray_angle, int x)
{
    t_ray_box sr;
    int hit = 0;

    init_send_ray_fn(&sr, data, ray_angle);

    while (!hit)
    {
        sr.ray_x += sr.ray_dir_x * 0.01;
        sr.ray_y += sr.ray_dir_y * 0.01;
        sr.map_x = (int)sr.ray_x;
        sr.map_y = (int)sr.ray_y;

        if (sr.map_x < 0 || sr.map_x >= data->file->max_len || sr.map_y < 0 || sr.map_y >= data->file->line_map)
            break;
        if (data->file->map[sr.map_y][sr.map_x] == '1')
        {
            double hit_x = 0;
            t_texture *texture = select_texture(data, sr.ray_dir_x, sr.ray_dir_y, &hit_x, sr.ray_x, sr.ray_y);
            double distance = calculate_corrected_distance(data, ray_angle, sr.ray_x, sr.ray_y);
            render_3d(data, distance, x, texture, hit_x);
            return distance;
        }
    }

    return 0;
}


void move_player(t_data *data){
	//W
	if (data->player.movey == 1 && data->file->map[(int)(data->player.y + (MOVE_SPEED * sin(data->player.angle)))][(int)(data->player.x + (MOVE_SPEED * cos(data->player.angle)))] == '0')
	{
		data->player.x += MOVE_SPEED * cos(data->player.angle);
		data->player.y += MOVE_SPEED * sin(data->player.angle);
	}
	// S
	if (data->player.movey == -1 && data->file->map[(int)(data->player.y - (MOVE_SPEED * sin(data->player.angle)))][(int)(data->player.x - (MOVE_SPEED * cos(data->player.angle)))] == '0'){ //S
		data->player.x -= MOVE_SPEED * cos(data->player.angle);
		data->player.y -= MOVE_SPEED * sin(data->player.angle);
	}
	
	// D
	if (data->player.movex == 1 && data->file->map[(int)(data->player.y + (MOVE_SPEED * cos(data->player.angle + PI / 2)))][(int)(data->player.x + (MOVE_SPEED * sin(data->player.angle + PI / 2)))] == '0') {
		data->player.x += MOVE_SPEED * cos(data->player.angle + PI / 2);
		data->player.y += MOVE_SPEED * sin(data->player.angle + PI / 2);
	}

	// A
	if (data->player.movex == -1 && data->file->map[(int)(data->player.y - (MOVE_SPEED * cos(data->player.angle + PI / 2)))][(int)(data->player.x - (MOVE_SPEED * sin(data->player.angle + PI / 2)))] == '0') {
		data->player.x -= MOVE_SPEED * cos(data->player.angle + PI / 2);
		data->player.y -= MOVE_SPEED * sin(data->player.angle + PI / 2);
	}
}

void ray_cast_radians(t_data *data)
{
    double ray_angle;
    double fov_radians = data->player.fov * (PI / 180.0);
    double angle_step = fov_radians / 1000;
    int i = 0;

    while (i++ < 1000)
    {
        ray_angle = data->player.angle - (fov_radians / 2) + (i * angle_step);
        send_ray(data, ray_angle, i);
    }

    move_player(data);
    draw_map(data);
    draw_fov(data);
}
