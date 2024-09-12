/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:46:52 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/12 15:41:49 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	init_color_struct(t_data *data)
{
	data->file->color = malloc(sizeof(t_color));
	if (!data->file->color)
	{
		free(data->file->path);
		free(data->file->map_line);
		free(data->file);
		error_alloc_file("Fail to allocate memory for path!");
	}
	data->file->color->f_r = ZERO_INIT;
	data->file->color->f_g = ZERO_INIT;
	data->file->color->f_b = ZERO_INIT;
	data->file->color->c_r = ZERO_INIT;
	data->file->color->c_g = ZERO_INIT;
	data->file->color->c_b = ZERO_INIT;
	data->file->color->f_set = ZERO_INIT;
	data->file->color->c_set = ZERO_INIT;
	data->file->color->f_check = ZERO_INIT;
	data->file->color->c_check = ZERO_INIT;
}

void	init_file_struct(t_data *data)
{
	data->file = malloc(sizeof(t_file));
	if (!data->file)
		error_alloc_file("Fail to allocate memory for file!");
	data->file->fd = ZERO_INIT;
	data->file->line_data = ZERO_INIT;
	data->file->line_map = ZERO_INIT;
	data->file->total_line = ZERO_INIT;
	data->file->infos = NULL;
	data->file->map = NULL;
}

void	init_path_struct(t_data *data)
{
	data->file->path = malloc(sizeof(t_path));
	if (!data->file->path)
	{
		free(data->file->map_line);
		free(data->file);
		error_alloc_file("Fail to allocate memory for path!");
	}
	data->file->path->path_no = NULL;
	data->file->path->path_so = NULL;
	data->file->path->path_we = NULL;
	data->file->path->path_ea = NULL;
	data->file->path->ea_check = ZERO_INIT;
	data->file->path->no_check = ZERO_INIT;
	data->file->path->so_check = ZERO_INIT;
	data->file->path->we_check = ZERO_INIT;
	init_color_struct(data);
}
