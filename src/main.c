/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:10:46 by whamdi            #+#    #+#             */
/*   Updated: 2024/09/27 17:00:55 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_lib.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	
	checker(argc, argv, envp);
	file_extractor(&data, argv[1]);
	file_cutter(&data);
	data_parser(&data);
	map_parser(&data);
	print_final_datas(&data);
	init_player(&data);
	for (int i = 0; i < data.file->line_map; i++)
	{
		for (int j = 0; j < data.file->max_len; j++)
		{
			if (data.file->map[i][j] == 'N' || data.file->map[i][j] == 'S' || data.file->map[i][j] == 'W'
				|| data.file->map[i][j] == 'E')
			{
				data.player.x = j;
				data.player.y = i;
				data.player.angle = get_angle_posplayer(data.file->map[i][j]);
				data.player.dir = data.file->map[i][j]; 
				break ;
			}
		}
	}
	printf("player x %f\t player y %f\n ", data.player.x, data.player.y);
	
	init_mlx(&data);
	mlx_hook(data.mlx.mlx_win, KeyPress, KeyPressMask, key_handler, &data);
	mlx_hook(data.mlx.mlx_win, 17, 0, free_close_windows, &data);
	mlx_loop_hook(data.mlx.p_mlx, minimap_render, (void *)&data);
	mlx_loop(data.mlx.p_mlx);
	free_file_struct(&data);
	return (0);
}
