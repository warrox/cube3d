/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyprien <cyprien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:24:01 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/11 01:51:31 by cyprien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	error_atoi(t_data *data, char *msg)
{
	free(data->file->color);
	free(data->file->path);
	free_split(data->file->tab_data);
	free(data->file->map_line_cpy);
	error_alloc_mapline(data, msg);
}

void	error_split_value(t_data *data, char *msg)
{
	free(data->file->color);
	free(data->file->path);
	free_split(data->file->tab_data);
	free(data->file->map_line_cpy);
	error_alloc_mapline(data, msg);
}

void	error_order(t_data *data, char *msg)
{
	free(data->file->color);
	free(data->file->path);
	free_split(data->file->tab_data);
	free(data->file->map_line_cpy);
	error_alloc_mapline(data, msg);
}
