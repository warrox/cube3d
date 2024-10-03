/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:28:35 by cyprien           #+#    #+#             */
/*   Updated: 2024/10/03 12:41:27 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	error_init_value(t_data *data, char **tmp, char *str, char **split)
{
	free_split(tmp);
	error_malloc_value(data, str, split,
		"Fail to malloc tmp_value (in set_value)!");
}

void	set_value(t_data *data, char *str, char **split)
{
	char	**tmp;
	char	**tmp_value;
	int		id_value;

	id_value = ZERO_INIT;
	tmp = NULL;
	tmp_value = NULL;
	tmp = ft_split(str, ' ');
	if (!tmp)
		error_malloc_value(data, str, split,
			"Fail to malloc tmp (in set_value)!");
	tmp_value = ft_split(tmp[1], ',');
	if (!tmp_value)
		error_init_value(data, tmp, str, split);
	if (ft_strncmp(tmp[0], "F", 2) == 0)
		id_value = F;
	else
		id_value = C;
	if (id_value == F)
		set_f_color(data, tmp_value);
	else
		set_c_color(data, tmp_value);
	free_split(tmp_value);
	free_split(tmp);
}

int	check_value(t_data *data, char *str, char **split)
{
	char	**tmp;
	char	**tmp_value;
	int		i;

	tmp = NULL;
	tmp_value = NULL;
	i = 1;
	tmp = ft_split(str, ' ');
	if (!tmp)
		error_malloc_value(data, str, split,
			"Fail to malloc tmp (in check_value)!");
	tmp_value = ft_split(tmp[1], ',');
	if (!tmp_value)
		error_init_value(data, tmp, str, split);
	i = 0;
	while (tmp_value[i])
	{
		if (!check_atoi_value(i, tmp_value, tmp))
			return (0);
		i++;
	}
	free_split(tmp_value);
	free_split(tmp);
	return (1);
}

int	check_syntax(char *str)
{
	int	i;
	int	count;

	i = 2;
	count = ZERO_INIT;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		if (!ft_isdigit(str[i]) && str[i] != ',')
			return (0);
		i++;
	}
	if (count != 2)
		return (0);
	return (1);
}

void	color_case(t_data *data, char *infos)
{
	char	**tmp;
	char	*cpy;
	int count;
	int	i;

	count = ZERO_INIT;
	i = ZERO_INIT;
	cpy = clear_whitespace(data, infos);
	tmp = ft_split(infos, ' ');
	if (!tmp)
		error_malloc_value(data, cpy, tmp,
			"Fail to malloc tmp (in color_case)!");
	while(tmp[i])
	{
		if (ft_isdigit(tmp[i][0]))
			count++;
		else 
		{
			if (tmp[i][0] == 'F' || tmp[i][0] == 'C' || tmp[i][0] == ',')
				count++;
		}
		i++;
	}
	// dprintf(2, "ICI %d\n", count);
	if (count != 2 && count != 4 && count != 5 && count != 6)
		error_malloc_value(data, cpy, tmp, "Error syntax detected in colors!");
	if (!check_syntax(cpy))
		error_malloc_value(data, cpy, tmp, "Error syntax detected in colors!");
	if (!check_value(data, cpy, tmp))
		error_malloc_value(data, cpy, tmp, "Error value detected in colors!");
	set_value(data, cpy, tmp);
	data->file->color->conv_c = convert_color_c(data);
	data->file->color->conv_f = convert_color_f(data);
	free_split(tmp);
	free(cpy);
}
