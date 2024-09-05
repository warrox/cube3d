/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:38:59 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/05 10:52:27 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	free_split(t_data *data)
{
	int	i;

	i = ZERO_INIT;
	while(data->map->data_tab[i])
	{
		free(data->map->data_tab[i]);
		i++;
	}
	free(data->map->data_tab);
}

void	free_map_struct(t_data *data)
{
	free_split(data);
	free(data->map->map_line_cpy);
	free(data->map);
}
