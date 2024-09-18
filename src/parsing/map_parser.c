/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:43:09 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/16 17:22:07 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	set_orientation(t_data *data, char **tmp, int i, int j)
{
	data->file->orientation = tmp[i][j];
	data->file->nb_player++;
}

int	check_walls(t_data *data)
{
	int		ea_we;
	int		no_s;
	int		inside_space;
	char	**tmp;

	ea_we = ZERO_INIT;
	no_s = ZERO_INIT;
	inside_space = ZERO_INIT;
	tmp = data->file->map;
	ea_we = check_ea_we_walls(data, tmp);
	no_s = check_no_s_walls(data, tmp);
	inside_space = check_in_space(data, tmp);
	if (ea_we && no_s && inside_space)
		return (1);
	return (0);
}

int	check_required_char(t_data *data)
{
	int		i;
	int		j;
	char	**tmp;

	i = ZERO_INIT;
	j = ZERO_INIT;
	tmp = data->file->map;
	while (i < data->file->line_map)
	{
		j = 0;
		while (tmp[i][j])
		{
			if (tmp[i][j] == 'N' || tmp[i][j] == 'S' || tmp[i][j] == 'E'
				|| tmp[i][j] == 'W')
				set_orientation(data, tmp, i, j);
			j++;
		}
		i++;
	}
	if (data->file->nb_player == 1)
		return (1);
	return (0);
}

int	check_char(t_data *data)
{
	int		i;
	int		j;
	char	**tmp;

	i = ZERO_INIT;
	j = ZERO_INIT;
	tmp = data->file->map;
	while (i < data->file->line_map)
	{
		j = 0;
		while (tmp[i][j])
		{
			if (tmp[i][j] != ' ' && tmp[i][j] != '\t' && tmp[i][j] != '1'
				&& tmp[i][j] != '0' && tmp[i][j] != 'N' && tmp[i][j] != 'S'
				&& tmp[i][j] != 'E' && tmp[i][j] != 'W')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	map_parser(t_data *data)
{
	if (!check_char(data))
		error_map(data, "Invalid char detected int map!");
	if (!check_required_char(data))
		error_map(data, "Missing required char or extra one detected!");
	if (!check_walls(data))
		error_map(data, "Map is not surrounded by walls!");
}
