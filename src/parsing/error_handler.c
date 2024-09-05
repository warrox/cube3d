/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:23:53 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/05 15:09:21 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	error_split(t_data *data)
{
	free(data->file->map_line_cpy);
	free(data->file);
	error_msg("Fail to allocate memory for tab_map!");
}

void	error_cpy(t_data *data, char *map_line)
{
	free(map_line);
	close(data->file->fd);
	free(data->file);
	error_msg("Fail to copy map!");
}

void	error_open(t_data *data, char *map_line)
{
	free(map_line);
	free(data->file);
	error_msg("Fail to open file!");
}

void	error_read(t_data *data, char *map_line, char *msg)
{
	free(map_line);
	close(data->file->fd);
	error_msg(msg);
}

void	error_msg(char *msg)
{
	printf("\033[31mError\n%s\n\033[0m", msg);
	exit(EXIT_FAILURE);
}
