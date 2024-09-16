/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:27:45 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/12 14:24:53 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	error_unexpected_info(t_data *data, char *msg)
{
	int	i;

	i = ZERO_INIT;
	free(data->file->color);
	free(data->file->path);
	free_split(data->file->tab_data);
	while (i < data->file->line_data)
	{
		free(data->file->infos[i]);
		i++;
	}
	i = 0;
	while (i < data->file->line_map)
	{
		free(data->file->map[i]);
		i++;
	}
	free(data->file->map);
	free(data->file->infos);
	free(data->file->map_line_cpy);
	free(data->file);
	printf("\033[31mError\n%s\n\033[0m", msg);
	exit(EXIT_FAILURE);
}

void	error_malloc_tmp(t_data *data, char *msg)
{
	int	i;

	i = ZERO_INIT;
	free(data->file->color);
	free(data->file->path);
	free_split(data->file->tab_data);
	while (i < data->file->line_data)
	{
		free(data->file->infos[i]);
		i++;
	}
	i = 0;
	while (i < data->file->line_map)
	{
		free(data->file->map[i]);
		i++;
	}
	free(data->file->map);
	free(data->file->infos);
	free(data->file->map_line_cpy);
	free(data->file);
	printf("\033[31mError\n%s\n\033[0m", msg);
	exit(EXIT_FAILURE);
}

void	error_malloc_fileinfos(t_data *data, char *msg)
{
	free(data->file->map);
	free(data->file->color);
	free(data->file->path);
	free_split(data->file->tab_data);
	free(data->file->map_line_cpy);
	free(data->file);
	printf("\033[31mError\n%s\n\033[0m", msg);
	exit(EXIT_FAILURE);
}

void	error_malloc_filemap(t_data *data, char *msg)
{
	free(data->file->color);
	free(data->file->path);
	free_split(data->file->tab_data);
	free(data->file->map_line_cpy);
	free(data->file);
	printf("\033[31mError\n%s\n\033[0m", msg);
	exit(EXIT_FAILURE);
}

void	error_data_format(t_data *data, char *msg)
{
	int	i;

	i = ZERO_INIT;
	free(data->file->color);
	free(data->file->path);
	while (i < data->file->line_data)
	{
		free(data->file->infos[i]);
		i++;
	}
	i = 0;
	while (i < data->file->line_map)
	{
		free(data->file->map[i]);
		i++;
	}
	free(data->file->map);
	free(data->file->infos);
	free_split(data->file->tab_data);
	free(data->file->map_line_cpy);
	free(data->file);
	printf("\033[31mError\n%s\n\033[0m", msg);
	exit(EXIT_FAILURE);
}
