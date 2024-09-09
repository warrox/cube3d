/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutter_utils_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:08:23 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/09 16:36:21 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	check_duplicate(t_data *data)
{
	if (data->color->f_check != 1 || data->color->c_check != 1)
	{
		dprintf(2, "ERROR DUPLICATE COLOR\n");
		// error;
		exit(1);
	}
	if (data->map->ea_check != 1 || data->map->so_check != 1 || data->map->we_check != 1 || data->map->no_check != 1)
	{
		dprintf(2, "ERROR DUPLICATE PATHS\n");
		// error;
		exit(1);
	}
}

void	count_data(t_data *data, char *id)
{
	if (detect_data(data, id) == F)
		data->color->f_check += 1;
	else if(detect_data(data, id) == C)
		data->color->c_check += 1;
	else if(detect_data(data, id) == EA)
		data->map->ea_check += 1;
	else if(detect_data(data, id) == NO)
		data->map->no_check += 1;
	else if(detect_data(data, id) == WE)
		data->map->we_check += 1;
	else if(detect_data(data, id) == SO)
		data->map->so_check += 1;
}
