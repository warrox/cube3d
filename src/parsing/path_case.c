/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:54:11 by cyprien           #+#    #+#             */
/*   Updated: 2024/09/17 15:17:15 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int	check_permission(char *path)
{
	if (access(path, F_OK) != 0)
		return (0);
	if (access(path, R_OK) != 0)
		return (0);
	return (1);
}

int	check_extension_path(char *str)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strncmp(str, "./", 2) != 0)
		return (0);
	if (ft_count_char(str, '.') != 2)
		return (0);
	tmp = ft_strrchr(str, '.');
	if (str)
	{
		if (ft_strcmp(tmp, ".xpm") != 0)
			return (0);
	}
	return (1);
}

int	check_syntax_path(char *str)
{
	int		i;
	char	**tmp;

	i = ZERO_INIT;
	tmp = NULL;
	tmp = ft_split(str, ' ');
	if (!tmp)
		return (0);
	while (tmp[i])
		i++;
	if (i != 2)
	{
		free_split(tmp);
		return (0);
	}
	free_split(tmp);
	return (1);
}

char	*clear_whitespace_path(t_data *data, char **tmp, char *str)
{
	int	count_char;

	count_char = count_clean_path_len(str);
	return (fill_clean_path(data, tmp, str, count_char));
}

void	path_case(t_data *data, char *str)
{
	char	*cpy;
	char	**tmp;

	(void)data;
	cpy = NULL;
	tmp = NULL;
	cpy = clear_whitespace_path(data, tmp, str);
	tmp = ft_split(cpy, ' ');
	if (!tmp)
		error_malloc_value(data, cpy, tmp,
			"Fail to allocate memory for tmp (in path_case)!");
	if (!check_syntax_path(str))
		error_malloc_value(data, cpy, tmp, "Syntax error in path!");
	if (!check_extension_path(tmp[1]))
		error_malloc_value(data, cpy, tmp, "Extension error in path!");
	if (!check_permission(tmp[1]))
		error_malloc_value(data, cpy, tmp, "No permission detected!");
	set_path(data, tmp);
	free_split(tmp);
	free(cpy);
}
