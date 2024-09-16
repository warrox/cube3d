/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_case_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:38:33 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/16 17:07:44 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int	check_atoi_value(int i, char **tmp_value, char **tmp)
{
	int	value;

	value = ft_atoi(tmp_value[i]);
	if (value < 0 || !(value >= 0 && value <= 255))
	{
		free_split(tmp_value);
		free_split(tmp);
		return (0);
	}
	return (1);
}

void	set_c_color(t_data *data, char **tmp_value)
{
	data->file->color->c_r = ft_atoi(tmp_value[0]);
	data->file->color->c_g = ft_atoi(tmp_value[1]);
	data->file->color->c_b = ft_atoi(tmp_value[2]);
}

void	set_f_color(t_data *data, char **tmp_value)
{
	data->file->color->f_r = ft_atoi(tmp_value[0]);
	data->file->color->f_g = ft_atoi(tmp_value[1]);
	data->file->color->f_b = ft_atoi(tmp_value[2]);
}
