/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:04:54 by cyferrei          #+#    #+#             */
/*   Updated: 2024/10/03 14:11:59 by cyferrei         ###   ########.fr       */
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
	printf("-----------FILE BEFORE PARSING-----------\n\n");
	print_file(data);
	printf("\n");
	printf("-----------FINALS DATA-----------\n");
	printf("final_F_r: %d\n", data->file->color->f_r);
	printf("final_F_g: %d\n", data->file->color->f_g);
	printf("final_F_b: %d\n", data->file->color->f_b);
	printf("final_C_r: %d\n", data->file->color->c_r);
	printf("final_C_g: %d\n", data->file->color->c_g);
	printf("final_C_b: %d\n", data->file->color->c_b);
	printf("----------------------------------------\n");
	printf("final_path_NO: %s\n", data->file->path->path_no);
	printf("final_path_WE: %s\n", data->file->path->path_we);
	printf("final_path_EA: %s\n", data->file->path->path_ea);
	printf("final_path_SO: %s\n", data->file->path->path_so);
	printf("----------------------------------------\n");
	printf("final_orientation: %c\n\n", data->file->orientation);
	printf("-----------FINALS MAP-----------\n");
	while (++i < data->file->line_map)
		printf("%s\n", data->file->map[i]);
	printf("----------------------------------------\n");
}
