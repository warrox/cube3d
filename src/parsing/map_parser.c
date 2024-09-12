/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:43:09 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/12 17:39:36 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

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
		while(tmp[i][j])
		{
			if (tmp[i][j] != ' ' && tmp[i][j] != '\t' && tmp[i][j] != '1' && 
				tmp[i][j] != '0' && tmp[i][j] != 'N' && tmp[i][j] != 'S' && 
				tmp[i][j] != 'E' && tmp[i][j] != 'W')
				{
					dprintf(2, "Invalid char: [%d] at i: %d j: %d\n", tmp[i][j], i, j);
					return (0);
				}
			j++;
		}
		i++;
	}
	return(1);
}

void	map_parser(t_data *data)
{
	if(!check_char(data))
	{
		dprintf(2, "INVALID CHAR IN MAP!\n");
		exit(1);
		// error;
	}
}