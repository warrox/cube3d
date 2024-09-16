/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:07:05 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/16 15:46:47 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	set_path(t_data *data, char **tmp)
{
	if (ft_strncmp(tmp[0], "NO", 2) == 0)
		data->file->path->path_no = ft_strdup(tmp[1]);
	else if (ft_strncmp(tmp[0], "WE", 2) == 0)
		data->file->path->path_we = ft_strdup(tmp[1]);
	else if (ft_strncmp(tmp[0], "EA", 2) == 0)
		data->file->path->path_ea = ft_strdup(tmp[1]);
	else if (ft_strncmp(tmp[0], "SO", 2) == 0)
		data->file->path->path_so = ft_strdup(tmp[1]);
}
