/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyprien <cyprien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:24:01 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/06 19:34:16 by cyprien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	error_atoi(t_data *data, char *msg)
{
	free_split(data->file->value);
	free_split(data->file->split_settings);
	free(data->color);
	free(data->map);
	free_split(data->file->tab_data);
	free(data->file->map_line_cpy);
	error_alloc_mapline(data, msg);
}

void	error_split_value(t_data *data, char *msg)
{
	free_split(data->file->split_settings);
	free(data->color);
	free(data->map);
	free_split(data->file->tab_data);
	free(data->file->map_line_cpy);
	error_alloc_mapline(data, msg);
}

void	error_order(t_data *data)
{
	free(data->color);
	free(data->map);
	free_split(data->file->tab_data);
	free(data->file->map_line_cpy);
	error_alloc_mapline(data, "Wrong order!");
}
