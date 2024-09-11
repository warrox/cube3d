/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyprien <cyprien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:23:53 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/11 01:50:18 by cyprien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	error_split(t_data *data)
{
	free(data->file->color);
	free(data->file->path);
	free(data->file->map_line_cpy);
	error_alloc_mapline(data, "Fail to allocate memory for tab_map!");
}

void	error_read(t_data *data, char *msg)
{
	close(data->file->fd);
	error_open(data, msg);
}

void	error_open(t_data *data, char *msg)
{
	free(data->file->color);
	free(data->file->path);
	free(data->file->map_line);
	error_alloc_mapline(data, msg);
}

void	error_alloc_mapline(t_data *data, char *msg)
{
	free(data->file);
	error_alloc_file(msg);
}

void	error_alloc_file(char *msg)
{
	printf("\033[31mError\n%s\n\033[0m", msg);
	exit(EXIT_FAILURE);
}
