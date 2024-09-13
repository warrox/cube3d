/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:29:35 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/13 16:27:11 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int	check_no_s_walls(t_data *data, char **map)
{
	int	i;
	int	j;
	int	tmp;
	

	tmp = data->file->line_map - 1;
	i = ZERO_INIT;
	j = ZERO_INIT;
	dprintf(2, "ICI_map[i]: %s\n", map[i]);
	dprintf(2, "ICI_map[tmp]: %s\n", map[tmp]);
	while(map[i][j] == ' ' || map[i][j] == '\t')
		j++;
	while(map[i][j])
	{
		if (map[i][j] != '1' && map[i][j] != ' ' && map[i][j] != '\t')
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
		if (map[tmp][j] != '1' && map[tmp][j] != ' ' && map[tmp][j] == '\t')
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