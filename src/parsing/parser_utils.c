/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:37:37 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/05 08:55:30 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

char	*new_alloc(t_data *data, char *ptr, int size)
{
	char	*new;

	new = NULL;
	free(ptr);
	new = malloc((size + 1) * sizeof(char));
	if (!new)
	{
		printf("\033[31mError\nFail to allocate memory for map_line!\n\033[0m");
		free(data->map);
		exit(EXIT_FAILURE);
	}
	return (new);
}
