/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:23:23 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/04 08:55:47 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int	open_file(char *file)
{
	int	fd;

	fd = ZERO_INIT;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("\033[31mError\nFail to open file!\n\033[0m");
		return (-1);
	}
	return (fd);
}

void	init_map_struct(t_data *data)
{
	data->map = malloc(sizeof(t_map));
	if (!data->map)
	{
		printf("\033[31mError\nFail to allocate memory for map!\n\033[0m");
		exit(EXIT_FAILURE);
	}
	data->map->line_map = NULL_INIT;
	data->map->fd = ZERO_INIT;
}

void	map_parser(t_data *data, char *file)
{
	init_map_struct(data);
	data->map->fd = open_file(file);
	if (data->map->fd == -1)
	{
		free(data->map);
		exit(EXIT_FAILURE);
	}
	else
		dprintf(2, "YES - %s\n", file);
	close(data->map->fd);
}