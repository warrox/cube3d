/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:46:52 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/05 17:49:30 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	init_color_struct(t_data *data)
{
	data->color = malloc(sizeof(t_color));
	if (!data->color)
	{
		;
		// error;
	}
	data->color->f_r = ZERO_INIT;
	data->color->f_g = ZERO_INIT;
	data->color->f_b = ZERO_INIT;
	data->color->c_r = ZERO_INIT;
	data->color->c_g = ZERO_INIT;
	data->color->c_b = ZERO_INIT;
	data->color->i = ZERO_INIT;
	data->color->j = ZERO_INIT;
}

void	init_file_struct(t_data *data)
{
	data->file = malloc(sizeof(t_file));
	if (!data->file)
		error_msg("Fail to allocate memory for map!");
	data->file->fd = ZERO_INIT;
	data->file->map_line_cpy = NULL;
	data->file->tab_data = NULL;
	data->file->value = ZERO_INIT;
}

void	init_map_struct(t_data *data)
{
	data->map = malloc(sizeof(t_map));
	if (!data->map)
	{
		//error
		;
	}
	data->map->path_no = NULL;
	data->map->path_so = NULL;
	data->map->path_we = NULL;
	data->map->path_ea = NULL;
	init_color_struct(data);
}