/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:10:18 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/13 17:01:07 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	check_order(t_data *data)
{
	int	i;
	char	*str;
	
	i = ZERO_INIT;
	str = data->file->map_line_cpy;
	while(str[i])
		i++;
	i--;
	if (str[i] != '1')
		error_data_format(data, "Error order: map is not last!");
	i = 0;
	while(str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == 'F' || str[i] == 'C' || str[i] == 'E' || str[i] == 'N'|| str[i] == 'W'|| str[i] == 'S')
		return;
	else
		error_data_format(data, "Error order: not expected format data!");
}

int	is_map_line(char *line)
{
	int	i;

	i = ZERO_INIT;
	while(line[i] == ' ' || line[i] == 't')
		i++;
	if(line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

void	split_data_map(t_data *data)
{
	int	i;
	int	map_idx;
	int	data_idx;
	
	map_idx = ZERO_INIT;
	data_idx = ZERO_INIT;
	i = ZERO_INIT;
	data->file->map = malloc(sizeof(char *) * data->file->line_map);
	if(!data->file->map)
		error_malloc_filemap(data, "Fail to malloc data->file->map!");
	data->file->infos = malloc(sizeof(char *) * data->file->line_data);
	if(!data->file->infos)
		error_malloc_fileinfos(data, "Fail to malloc data->file->infos!");
	while(i < data->file->total_line)
	{
		if(is_map_line(data->file->tab_data[i]))
			data->file->map[map_idx++] = ft_strdup(data->file->tab_data[i]);
		else
			data->file->infos[data_idx++] = ft_strdup(data->file->tab_data[i]);
		i++;
	}
}

void	count_line(t_data *data)
{
	int	i;

	i = ZERO_INIT;
	while(data->file->tab_data[i])
		i++;
	data->file->total_line = i;
	i = 0;
	while(i < data->file->total_line)
	{
		if(is_map_line(data->file->tab_data[i]))
			data->file->line_map++;
		else
			data->file->line_data++;
		i++;
	}
}

void	file_cutter(t_data *data)
{
	data->file->tab_data = ft_split(data->file->map_line_cpy, '\n');
	if (!data->file->tab_data)
		error_split(data);
	count_line(data);
	split_data_map(data);
	check_order(data);
}
