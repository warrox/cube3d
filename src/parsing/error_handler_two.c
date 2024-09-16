/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:31:30 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/16 17:13:38 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	end_error(t_data *data, char *msg)
{
	int	i;

	i = ZERO_INIT;
	while (i < data->file->line_map)
	{
		free(data->file->map[i]);
		i++;
	}
	free(data->file->map);
	free(data->file->infos);
	free(data->file->map_line_cpy);
	free(data->file);
	printf("\033[31mError\n%s\n\033[0m", msg);
	exit(EXIT_FAILURE);
}

void	error_map(t_data *data, char *msg)
{
	int	i;

	i = ZERO_INIT;
	free(data->file->path->path_ea);
	free(data->file->path->path_no);
	free(data->file->path->path_so);
	free(data->file->path->path_we);
	free(data->file->color);
	free(data->file->path);
	free_split(data->file->tab_data);
	while (i < data->file->line_data)
	{
		free(data->file->infos[i]);
		i++;
	}
	end_error(data, msg);
}

void	error_malloc_whtspc(t_data *data, char *str, char *msg)
{
	int	i;

	i = ZERO_INIT;
	free(str);
	if (data->file->path->path_ea != NULL)
		free(data->file->path->path_ea);
	if (data->file->path->path_no != NULL)
		free(data->file->path->path_no);
	if (data->file->path->path_so != NULL)
		free(data->file->path->path_so);
	if (data->file->path->path_we != NULL)
		free(data->file->path->path_we);
	free(data->file->color);
	free(data->file->path);
	free_split(data->file->tab_data);
	while (i < data->file->line_data)
	{
		free(data->file->infos[i]);
		i++;
	}
	end_error(data, msg);
}

void	error_malloc_value(t_data *data, char *str, char **split, char *msg)
{
	int	i;

	i = ZERO_INIT;
	free_split(split);
	free(str);
	if (data->file->path->path_ea != NULL)
		free(data->file->path->path_ea);
	if (data->file->path->path_no != NULL)
		free(data->file->path->path_no);
	if (data->file->path->path_so != NULL)
		free(data->file->path->path_so);
	if (data->file->path->path_we != NULL)
		free(data->file->path->path_we);
	free(data->file->color);
	free(data->file->path);
	free_split(data->file->tab_data);
	while (i < data->file->line_data)
	{
		free(data->file->infos[i]);
		i++;
	}
	end_error(data, msg);
}
