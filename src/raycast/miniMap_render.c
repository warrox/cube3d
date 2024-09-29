#include "../../includes/cub3D_lib.h"

void draw_fov(t_data *data)
{
    double fov = 60 * (PI / 180.0);
    double half_fov = fov / 2;  
    int num_rays = 100; 
    double angle_step = fov / num_rays; 
    double ray_angle, ray_dir_x, ray_dir_y;
    double ray_x, ray_y;
    int hit, map_x, map_y;

    // Position du joueur sur la mini-map
    int player_pos[2];
    player_pos[0] = data->player.x * data->cell_width;
    player_pos[1] = data->player.y * data->cell_height;

    for (int i = 0; i < num_rays; i++)
    {
        ray_angle = data->player.angle - half_fov + (i * angle_step);

        ray_dir_x = cos(ray_angle);
        ray_dir_y = sin(ray_angle);

        ray_x = data->player.x;
        ray_y = data->player.y;
        hit = 0;

        while (!hit)
        {
            ray_x += ray_dir_x * 0.1;
            ray_y += ray_dir_y * 0.1;

            map_x = (int)ray_x;
            map_y = (int)ray_y;

            if (map_x >= 0 && map_x < data->file->max_len && map_y >= 0 && map_y < data->file->line_map && data->file->map[map_y][map_x] == '1')
            {
                hit = 1;
            }

            if (map_x < 0 || map_x >=data->file->max_len  || map_y < 0 || map_y >= data->file->line_map)
            {
                hit = 1;
            }
        }

        int arrival_pos[2];
        arrival_pos[0] = ray_x * data->cell_width;
        arrival_pos[1] = ray_y * data->cell_height;
        draw_line_fov_minim(data, player_pos, arrival_pos, 0xFF0000);
    }
}

void draw_line_fov_minim(t_data *data, int pos1[2], int pos2[2], int color)
{
    int x0 = pos1[0]; // Coordonnée x du point 1
    int y0 = pos1[1]; // Coordonnée y du point 1
    int x1 = pos2[0]; // Coordonnée x du point 2
    int y1 = pos2[1]; // Coordonnée y du point 2

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;
    int e2;
    while (1)
    {
		img_pix_put(data, x0, y0, color);
        if (x0 == x1 && y0 == y1) // Si la ligne est complète
            break;

        e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

