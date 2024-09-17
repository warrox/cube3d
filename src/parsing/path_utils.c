/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:07:05 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/17 15:22:28 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

char	*fill_clean_path(t_data *data, char **tmp, char *str, int count_char)
{
	int		i;
	int		j;
	int		flag;
	char	*clear_path;

	i = -1;
	j = 0;
	flag = 0;
	clear_path = malloc((sizeof(char) * count_char) + 2);
	if (!clear_path)
		error_malloc_value(data, str, tmp, "Error malloc!");
	while (str[++i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		clear_path[j] = str[i];
		flag++;
		if (flag == 2)
		{
			j++;
			clear_path[j] = ' ';
		}
		j++;
	}
	return (clear_path[j] = '\0', clear_path);
}

int	count_clean_path_len(const char *str)
{
	int	i;
	int	count_char;

	i = 0;
	count_char = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		count_char++;
		i++;
	}
	return (count_char);
}

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
