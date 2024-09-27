/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:04:54 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/24 12:30:38 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	print_file(t_data *data)
{
	print_split(data->file->tab_data);
}

void	print_final_datas(t_data *data)
{
	int	i;

	i = -1;
	dprintf(2, "-----------FILE BEFORE PARSING-----------\n\n");
	print_file(data);
	dprintf(2, "\n");
	dprintf(2, "-----------FINALS DATA-----------\n");
	dprintf(2, "final_F_r: %d\n", data->file->color->f_r);
	dprintf(2, "final_F_g: %d\n", data->file->color->f_g);
	dprintf(2, "final_F_b: %d\n", data->file->color->f_b);
	dprintf(2, "final_C_r: %d\n", data->file->color->c_r);
	dprintf(2, "final_C_g: %d\n", data->file->color->c_g);
	dprintf(2, "final_C_b: %d\n", data->file->color->c_b);
	dprintf(2, "----------------------------------------\n");
	dprintf(2, "final_path_NO: %s\n", data->file->path->path_no);
	dprintf(2, "final_path_WE: %s\n", data->file->path->path_we);
	dprintf(2, "final_path_EA: %s\n", data->file->path->path_ea);
	dprintf(2, "final_path_SO: %s\n", data->file->path->path_so);
	dprintf(2, "----------------------------------------\n");
	dprintf(2, "final_orientation: %c\n\n", data->file->orientation);
	dprintf(2, "-----------FINALS MAP-----------\n");
	while (++i < data->file->line_map)
		dprintf(2, "%s\n", data->file->map[i]);
	dprintf(2, "----------------------------------------\n");
}
