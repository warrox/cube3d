/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:23:23 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/04 11:07:26 by cyferrei         ###   ########.fr       */
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
	data->map->line_map = NULL;
	data->map->fd = ZERO_INIT;
}

void	map_parser(t_data *data, char *file)
{
	char	*map_line;
	int		bytes_read;
	int		size_read;

	bytes_read = 1;
	size_read = 2048;
	map_line = malloc(size_read * sizeof(char));
	if (!map_line)
	{
		printf("\033[31mError\nFail to allocate memory for map_line!\n\033[0m");
		exit(EXIT_FAILURE);
	}
	init_map_struct(data);
	data->map->fd = open_file(file);
	while (1)
	{
		bytes_read = read(data->map->fd, map_line, size_read - 1);
		if (bytes_read < 0)
		{
			perror("Error reading file");
			free(map_line);
			close(data->map->fd);
			exit(EXIT_FAILURE);
		}
		if (bytes_read < size_read - 1)
			break ;
		size_read *= 2;
		map_line = new_alloc(data, map_line, size_read);
	}
	map_line[bytes_read] = '\0';
	close(data->map->fd);
	dprintf(2, "MAP_LINE-> %s\n", map_line);
	free(map_line);
	dprintf(2, "DONE!\n");
}
