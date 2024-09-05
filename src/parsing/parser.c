/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:23:23 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/05 18:19:48 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int	open_file(char *file)
{
	int	fd;

	fd = ZERO_INIT;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

void	cpy_map_data(t_data *data, char *map_line)
{
	data->file->map_line_cpy = ft_strdup(map_line);
	if (!data->file->map_line_cpy)
		error_cpy(data, map_line);
	close(data->file->fd);
	free(map_line);
}

void	file_parser(t_data *data, char *file)
{
	char	*map_line;
	int		bytes_read;
	int		size_read;

	bytes_read = 1;
	size_read = 2048;
	map_line = malloc(size_read * sizeof(char));
	if (!map_line)
		error_msg("Fail to allocate memory for map_line!");
	init_file_struct(data);
	init_map_struct(data);
	data->file->fd = open_file(file);
	if (data->file->fd == -1)
		error_open(data, map_line);
	while (1)
	{
		bytes_read = read(data->file->fd, map_line, size_read - 1);
		if (bytes_read < 0)
			error_read(data, map_line, "Error while reading file!");
		if (bytes_read < size_read - 1)
			break ;
		size_read *= 2;
		map_line = new_alloc(data, map_line, size_read);
	}
	map_line[bytes_read] = '\0';
	cpy_map_data(data, map_line);
}
