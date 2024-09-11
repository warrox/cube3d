/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyprien <cyprien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:38:59 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/11 01:34:41 by cyprien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	free_split(char **split)
{
	int	i;

	i = ZERO_INIT;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_file_struct(t_data *data)
{
	free(data->file->map_line_cpy);
	free_split(data->file->tab_data);
	free(data->file->color);
	free(data->file->path);
	free(data->file);
}
