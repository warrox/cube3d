/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutter_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:07:03 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/24 12:12:16 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	allocate_file_maps(t_data *data)
{
	data->file->map = malloc(sizeof(char *) * data->file->line_map);
	if (!data->file->map)
		error_malloc_filemap(data, "Fail to malloc data->file->map!");
	data->file->infos = malloc(sizeof(char *) * data->file->line_data);
	if (!data->file->infos)
		error_malloc_fileinfos(data, "Fail to malloc data->file->infos!");
}

void	process_data_map(t_data *data)
{
	int	i;
	int	map_idx;
	int	data_idx;

	map_idx = ZERO_INIT;
	data_idx = ZERO_INIT;
	i = -1;
	while (++i < data->file->total_line)
	{
		if (is_map_line(data->file->tab_data[i]))
			find_max_len(data, data->file->tab_data[i]);
	}
	i = -1;
	while (++i < data->file->total_line)
	{
		if (is_map_line(data->file->tab_data[i]))
			fill_map(data, data->file->tab_data[i],
				&data->file->map[map_idx++]);
		else
			data->file->infos[data_idx++] = ft_strdup(data->file->tab_data[i]);
	}
}
