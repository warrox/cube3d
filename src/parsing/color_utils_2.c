/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:55:40 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/24 14:22:09 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int	create_rgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	convert_color_c(t_data *data)
{
	return (create_rgb(0, data->file->color->c_r, data->file->color->c_g,
			data->file->color->c_b));
}

int	convert_color_f(t_data *data)
{
	return (create_rgb(0, data->file->color->f_r, data->file->color->f_g,
			data->file->color->f_b));
}
