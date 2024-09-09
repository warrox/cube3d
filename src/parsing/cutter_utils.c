/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:17:15 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/09 11:47:15 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	print_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
	{
		printf("Le split est nul.\n");
		return ;
	}
	while (split[i])
	{
		printf("Element %d: %s\n", i, split[i]);
		i++;
	}
}

void	check_syntax(t_data *data, char **split)
{
	int	i;
	int	j;

	i = ZERO_INIT;
	j = ZERO_INIT;
	while (split[i])
	{
		j = 0;
		if (i == 0)
		{
			while (split[i][j] == ' ' || split[i][j] == '\t')
				j++;
			if (split[i][j] != 'F' || split[i][j] != 'C')
				error_split_value(data, "Not a valid format for color!");
		}
		i++;
	}
}

void	check_nb_colors(t_data *data, char **split)
{
	int	i;

	i = ZERO_INIT;
	while (split[i])
		i++;
	// dprintf(2, "ICI %d\n", i);
	if (i != 4)
		error_split_value(data, "Not a valid format for color!");
}

void	set_value_settings(t_data *data, int value, int c_or_g, int rgb)
{
	if (c_or_g == F)
	{
		if (rgb == R)
			data->color->f_r = value;
		else if (rgb == G)
			data->color->f_g = value;
		else
			data->color->f_b = value;
	}
	if (c_or_g == C)
	{
		if (rgb == R)
			data->color->c_r = value;
		else if (rgb == G)
			data->color->c_g = value;
		else
			data->color->c_b = value;
	}
}

void	check_convert(t_data *data, char *str, int c_or_g, int rgb)
{
	int	i;
	int	value;

	i = ZERO_INIT;
	value = ZERO_INIT;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		error_atoi(data, "Error while atoi!");
	value = ft_atoi(str);
	if (value < 0 || value > 255)
		error_atoi(data, "Color value must be between 0 and 255!");
	else
		set_value_settings(data, value, c_or_g, rgb);
}

void	set_value(t_data *data, char **split, int c_or_g)
{
	int	i;

	i = 1;
	check_nb_colors(data, split);
	print_split(split);
	// check_syntax(data, split);
	while (split[i])
	{
		data->file->value = ft_split(split[i], ',');
		if (!data->file->value)
			error_split_value(data, "Error while splitting value!");
		check_convert(data, data->file->value[0], c_or_g, (i - 1));
		free_split(data->file->value);
		i++;
	}
}
