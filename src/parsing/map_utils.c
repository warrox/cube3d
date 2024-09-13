/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:29:35 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/13 17:36:49 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int	check_in_space(t_data *data, char **map)
{
	int	i;
	int	j;
	int	tmp;

	i = ZERO_INIT;
	j = ZERO_INIT;
	tmp = data->file->line_map;
	while(i < tmp)
	{
		// check_arround_space;
		i++;
	}
	return(0);
}

int	check_no_s_walls(t_data *data, char **map)
{
	int	j;
	int	tmp;
	
	tmp = data->file->line_map - 1;
	j = ZERO_INIT;
	while(map[0][j] == ' ' || map[0][j] == '\t')
		j++;
	while(map[0][j])
	{
		if (map[0][j] == '0')
		{
			dprintf(2, "line_N\n");
			return (0);
		}
		j++;
	}
	j = 0;
	while(map[tmp][j] == ' ' || map[tmp][j] == '\t')
		j++;
	while(map[tmp][j])
	{
		if (map[tmp][j] == '0')
		{
			dprintf(2, "line_S\n");
			return (0);
		}
		j++;
	}
	return (1);
}

int	check_ea_we_walls(t_data *data, char **map)
{
	int	i;
	int	j;

	i = ZERO_INIT;
	j = ZERO_INIT;
	while(i < data->file->line_map)
	{
		j = 0;
		while(map[i][j] == ' ' || map[i][j] == '\t')
				j++;
		if (map[i][j] != '1')
			return (0);
		while(map[i][j])
			j++;
		if (map[i][j - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}