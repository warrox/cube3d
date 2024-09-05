/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:10:18 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/05 11:38:40 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	check_order_data(t_data *data)
{
	int	i;
	int	j;
	char	comp;
	
	i = ZERO_INIT;
	j = ZERO_INIT;
	while(data->map->data_tab[i][j] == ' ' || data->map->data_tab[i][j] == '\t')
		j++;
	comp = data->map->data_tab[i][j];
	dprintf(2, "TOP ->[%c]\n", comp);
	if (comp != 'N' && comp != 'S' && comp != 'W' && comp != 'E' && comp != 'F' && comp != 'C')
			error_order(data);
	dprintf(2, "\033[32mSeems good...\033[0m\n");
}

void	file_cutter(t_data *data)
{
	int	i;
	
	i = ZERO_INIT;
	data->map->data_tab = ft_split(data->map->map_line_cpy, '\n');
	if (!data->map->data_tab)
		error_split(data);
	while(data->map->data_tab[i])
	{
		printf("[%s]\n", data->map->data_tab[i]);
		i++;
	}
	check_order_data(data);
}