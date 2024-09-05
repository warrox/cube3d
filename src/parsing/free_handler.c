/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:38:59 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/05 17:37:25 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	free_split(char **split)
{
	int	i;

	i = ZERO_INIT;
	while(split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_file_struct(t_data *data)
{
	free_split(data->file->tab_data);
	free(data->file->map_line_cpy);
	free(data->file);
}
