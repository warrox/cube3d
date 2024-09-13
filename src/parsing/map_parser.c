/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:43:09 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/13 16:27:47 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int	check_walls(t_data *data)
{
	int	ea_we;
	int	no_s;
	char	**tmp;

	ea_we = ZERO_INIT;
	no_s = ZERO_INIT;
	tmp = data->file->map;
	ea_we = check_ea_we_walls(data, tmp);
	no_s = check_no_s_walls(data, tmp);
	if(ea_we)
		dprintf(2, "\033[38;5;76mea_we_walls OK\033[0m\n");
	else
	 	dprintf(2, "\033[38;5;196mea_we_walls KO\033[0m\n");
	if(no_s)
		dprintf(2, "\033[38;5;76mno_s_walls OK\033[0m\n");
	else
		dprintf(2, "\033[38;5;196mno_s_walls KO\033[0m\n");
	if (ea_we && no_s)
		return (1);
	return (0);	
}
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
	if (!check_walls(data))
		error_map(data, "Map is not surrounded by walls!");
}