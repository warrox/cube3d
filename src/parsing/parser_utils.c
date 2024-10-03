/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:37:37 by cyferrei          #+#    #+#             */
/*   Updated: 2024/10/03 13:30:39 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int	check_around_character(char **map, int i, int j, int line_len[3])
{
	if ((j - 1 >= 0 && j - 1 <= line_len[0] && map[i - 1][j - 1] == ' ')
		|| (j <= line_len[0] && map[i - 1][j] == ' ') || (j + 1 <= line_len[0]
			&& map[i - 1][j + 1] == ' ') || (j - 1 >= 0 && j - 1 <= line_len[2]
			&& map[i + 1][j - 1] == ' ') || (j <= line_len[2] && map[i
			+ 1][j] == ' ') || (j + 1 <= line_len[2] && map[i + 1][j
			+ 1] == ' ') || (j + 1 < line_len[1] && map[i][j + 1] == ' ') || (j
			- 1 >= 0 && map[i][j - 1] == ' '))
	{
		return (1);
	}
	return (0);
}


char	*new_alloc(t_data *data, char *ptr, int size)
{
	char	*new;

	new = NULL;
	free(ptr);
	new = malloc((size + 1) * sizeof(char));
	if (!new)
	{
		printf("\033[31mError\nFail to allocate memory for map_line!\n\033[0m");
		close(data->file->fd);
		free(data->file->color);
		free(data->file->path);
		free(data->file);
		exit(EXIT_FAILURE);
	}
	return (new);
}
