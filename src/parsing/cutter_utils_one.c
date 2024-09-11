/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutter_utils_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyprien <cyprien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:08:23 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/11 01:22:05 by cyprien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/cub3D_lib.h"

// void	init_detector(t_data *data, int i, int j)
// {
// 	while (data->file->tab_data[i][j] == ' '
// 		|| data->file->tab_data[i][j] == '\t')
// 		j++;
// 	// dprintf(2, "{I}: %d\n", i);
// 	data->file->split_settings = ft_split(data->file->tab_data[i], ',');
// 	if (!data->file->split_settings)
// 		error_order(data, "Fail to allocate memory for split_settings");
// 	print_split(data->file->split_settings);
// 	data->file->value = ft_split(data->file->split_settings[0], ' ');
// 	if (!data->file->value)
// 	{
// 		free_split(data->file->split_settings);
// 		error_order(data, "Fail to allocate memory for split_value");
// 	}
// }

// int	data_detector(t_data *data, int var)
// {
// 	if (var == F || var == C)
// 	{
// 		set_color(data, data->file->split_settings, var);
// 		return (1);
// 	}
// 	else if (var == EA || var == NO || var == WE || var == SO)
// 	{
// 		dprintf(2, "ICI-> PATH DETETECTED %d\n", var);
// 		return (1);
// 	}
// 	else
// 	{
// 		free_split(data->file->split_settings);
// 		error_order(data, "Not excpected value in data!");
// 		return (-1);
// 	}
// }

// void	check_duplicate(t_data *data)
// {
// 	if (data->color->f_check != 1 || data->color->c_check != 1)
// 		error_order(data, "Error duplicate color!");
// 	if (data->map->ea_check != 1 || data->map->so_check != 1
// 		|| data->map->we_check != 1 || data->map->no_check != 1)
// 		error_order(data, "Error duplicate path!");
// }

// void	count_data(t_data *data, char *id)
// {
// 	if (detect_data(data, id) == F)
// 		data->color->f_check += 1;
// 	else if (detect_data(data, id) == C)
// 		data->color->c_check += 1;
// 	else if (detect_data(data, id) == EA)
// 		data->map->ea_check += 1;
// 	else if (detect_data(data, id) == NO)
// 		data->map->no_check += 1;
// 	else if (detect_data(data, id) == WE)
// 		data->map->we_check += 1;
// 	else if (detect_data(data, id) == SO)
// 		data->map->so_check += 1;
// }
