/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:43:09 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/13 15:18:15 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int	check_required_char(t_data *data)
{
	int	i;
	int	j;
	char	**tmp;
	int	player;
	
	i = ZERO_INIT;
	j = ZERO_INIT;
	player = ZERO_INIT;
	tmp = data->file->map;
	while(i < data->file->line_map)
	{
		j = 0;
		while(tmp[i][j])
		{
			if (tmp[i][j] == 'N' || tmp[i][j] == 'S' || tmp[i][j] == 'E' || tmp[i][j] == 'W')
			{
				data->file->orientation = tmp[i][j];
				player++;
			}
			j++;
		}
		i++;
	}
	//dprintf(2, "PLAYER: %d\n", player);
	if(player == 1)
		return (1);
	return (0);
}

int	check_char(t_data *data)
{
	int	i;
	int	j;
	char **tmp;
	
	i = ZERO_INIT;
	j = ZERO_INIT;
	tmp = data->file->map;
	while(i < data->file->line_map)
	{
		j = 0;
		while(tmp[i][j])
		{
			if (tmp[i][j] != ' ' && tmp[i][j] != '\t' && tmp[i][j] != '1' && 
				tmp[i][j] != '0' && tmp[i][j] != 'N' && tmp[i][j] != 'S' && 
				tmp[i][j] != 'E' && tmp[i][j] != 'W')
					return (0);

			j++;
		}
		i++;
	}
	return(1);
}

void	map_parser(t_data *data)
{
	if(!check_char(data))
		error_map(data, "Invalid char detected int map!");
	if (!check_required_char(data))
		error_map(data, "Missing required char or extra one detected!");
}