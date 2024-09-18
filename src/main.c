/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:10:46 by whamdi            #+#    #+#             */
/*   Updated: 2024/09/18 14:15:40 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_lib.h"

// implement a calculation function to build the fov
char	map[MAP_HEIGHT][MAP_WIDTH + 1] = 
	{
		"111111", 
		"101001", 
		"101001",
		"10S001", 
		"111111"};

int cpy_map(t_data *data)
{

	int i = 0;
	data->map_test = malloc(sizeof(char*) * (MAP_HEIGHT + 1));
	if (!data->map_test)
		return (0);

	while (i < MAP_HEIGHT)
	{
		data->map_test[i] = ft_strdup(map[i]);
		if (!data->map_test[i])
		{
			while (i > 0)
				free(data->map_test[--i]);
			free(data->map_test);
			return (0);
		}
		i++;
	}
	data->map_test[i] = NULL;
	return(0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	
	(void)argc;
	(void)argv;
	(void)envp;
	// checker(argc, argv, envp);
	// file_extractor(&data, argv[1]);
	// file_cutter(&data);
	// data_parser(&data);
	// map_parser(&data);
	// print_final_datas(&data);
	// carte vérification
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		printf("%s\n", map[i]);
	}
	init_player(&data);
	cpy_map(&data);
	// Rechercher la position initiale du joueur
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E')
			{
				data.player.x = j;
				data.player.y = i;
				data.player.angle = get_angle_posplayer(map[i][j]);
				data.player.dir = map[i][j];
				break ;
			}
		}
	}
	printf("player x %f\t player y %f\n ", data.player.x, data.player.y);
	init_mlx(&data);
	mlx_hook(data.mlx.mlx_win, KeyPress, KeyPressMask, key_handler, &data);
	mlx_loop_hook(data.mlx.p_mlx, minimap_render, (void *)&data);
	mlx_loop(data.mlx.p_mlx);
	// free_file_struct(&data);
	return (0);
}
