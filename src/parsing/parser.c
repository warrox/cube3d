/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyprien <cyprien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:23:23 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/06 18:55:45 by cyprien          ###   ########.fr       */
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

void	cpy_map_data(t_data *data)
{
	data->file->map_line_cpy = ft_strdup(data->file->map_line);
	if (!data->file->map_line_cpy)
		error_read(data, "Error while copying file!");
	close(data->file->fd);
	free(data->file->map_line);
}

void	file_parser(t_data *data, char *file)
{
	int		bytes_read;
	int		size_read;

	bytes_read = 1;
	size_read = 2048;
	init_file_struct(data);
	data->file->map_line = malloc(size_read * sizeof(char));
	if (!data->file->map_line)
		error_alloc_mapline(data, "Fail to allocate memory for map_line!");
	init_map_struct(data);
	data->file->fd = open_file(file);
	if (data->file->fd == -1)
		error_open(data, "Error while opening file!");
	while (1)
	{
		bytes_read = read(data->file->fd, data->file->map_line, size_read - 1);
		if (bytes_read < 0)
			error_read(data, "Error while reading file!");
		if (bytes_read < size_read - 1)
			break ;
		size_read *= 2;
		data->file->map_line = new_alloc(data, data->file->map_line, size_read);
	}
	data->file->map_line[bytes_read] = '\0';
	cpy_map_data(data);
}
