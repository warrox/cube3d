/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:29:35 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/18 16:37:43 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int	check_around_space(char **map, int i, int j, int line_len[3])
{
	if ((j - 1 >= 0 && j - 1 <= line_len[0] && map[i - 1][j - 1] == '0')
		|| (j <= line_len[0] && map[i - 1][j] == '0') || (j + 1 <= line_len[0]
			&& map[i - 1][j + 1] == '0') || (j - 1 >= 0 && j - 1 <= line_len[2]
			&& map[i + 1][j - 1] == '0') || (j <= line_len[2] && map[i
			+ 1][j] == '0') || (j + 1 <= line_len[2] && map[i + 1][j
			+ 1] == '0') || (j + 1 < line_len[1] && map[i][j + 1] == '0') || (j
			- 1 >= 0 && map[i][j - 1] == '0'))
	{
		return (1);
	}
	return (0);
}

int	check_in_space(t_data *data, char **map)
{
	int	i;
	int	j;
	int	last_line;
	int	line_len[3];

	i = 1;
	last_line = data->file->line_map - 1;
	while (i < last_line)
	{
		line_len[0] = ft_strlen(map[i - 1]);
		line_len[1] = ft_strlen(map[i]);
		line_len[2] = ft_strlen(map[i + 1]);
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(" \t", map[i][j]) && check_around_space(map, i, j,
					line_len))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_no_s_walls(t_data *data, char **map)
{
	int	j;
	int	tmp;

	tmp = data->file->line_map - 1;
	j = ZERO_INIT;
	while (map[0][j] == ' ' || map[0][j] == '\t')
		j++;
	while (map[0][j])
	{
		if (map[0][j] == '0')
			return (0);
		j++;
	}
	j = 0;
	while (map[tmp][j] == ' ' || map[tmp][j] == '\t')
		j++;
	while (map[tmp][j])
	{
		if (map[tmp][j] == '0')
			return (0);
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
	while (i < data->file->line_map)
	{
		j = 0;
		while (map[i][j] == ' ' || map[i][j] == '\t')
			j++;
		if (map[i][j] != '1')
			return (0);
		while (map[i][j])
			j++;
		if (map[i][j - 1] != '1' && map[i][j - 1] != ' ')
			return (0);
		i++;
	}
	return (1);
}
