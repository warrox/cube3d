/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:10:46 by whamdi            #+#    #+#             */
/*   Updated: 2024/10/07 11:20:42 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_lib.h"

void	init_angle_player(t_data *data)
{
	int	i;
	int	j;

	file_cutter(data);
	data_parser(data);
	map_parser(data);
	init_player(data);
	i = -1;
	while (++i < data->file->line_map)
	{
		j = -1;
		while (++j <= data->file->max_len)
		{
			if (data->file->map[i][j] == 'N' || data->file->map[i][j] == 'S'
				|| data->file->map[i][j] == 'W' || data->file->map[i][j] == 'E')
			{
				data->player.x = j + 0.25;
				data->player.y = i + 0.25;
				data->player.angle = get_angle_posplayer(data->file->map[i][j]);
				data->player.dir = data->file->map[i][j];
				break ;
			}
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	checker(argc, argv, envp);
	file_extractor(&data, argv[1]);
	init_angle_player(&data);
	init_mlx(&data);
	load_texture(&data);
	mlx_hook(data.mlx.mlx_win, KeyPress, KeyPressMask, key_handler, &data);
	mlx_hook(data.mlx.mlx_win, KeyRelease, KeyReleaseMask, key_release_handler,
		&data);
	mlx_hook(data.mlx.mlx_win, 17, 0, free_close_windows, &data);
	mlx_loop_hook(data.mlx.p_mlx, minimap_render, (void *)&data);
	mlx_loop(data.mlx.p_mlx);
	mlx_destroy_window(data.mlx.p_mlx, data.mlx.mlx_win);
	mlx_destroy_image(data.mlx.p_mlx, data.mlx.img);
	if (data.no.img)
		mlx_destroy_image(data.mlx.p_mlx, data.no.img);
	if (data.so.img)
		mlx_destroy_image(data.mlx.p_mlx, data.so.img);
	if (data.ea.img)
		mlx_destroy_image(data.mlx.p_mlx, data.ea.img);
	if (data.we.img)
		mlx_destroy_image(data.mlx.p_mlx, data.we.img);
	free_file_struct(&data);
	return (0);
}
