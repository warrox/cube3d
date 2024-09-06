/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyprien <cyprien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:17:15 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/06 19:36:40 by cyprien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

#include <stdio.h>

void print_split(char **split)
{
	int i = 0;

	if (!split)
	{
		printf("Le split est nul.\n");
		return;
	}

	while (split[i])
	{
		printf("Element %d: %s\n", i, split[i]);
		i++;
	}
}

void	set_value_settings(t_data *data, int value, int c_or_g, int rgb)
{
	if (c_or_g == F)
	{
		dprintf(2, "[value: %d]\n", value);
		if(rgb == R)
		{
			data->color->f_r = value;
			dprintf(2, "[value f_r: %d]\n", data->color->f_r);
		}
		else if(rgb == G)
			data->color->f_g = value;
		else
			data->color->f_b = value;
		dprintf(2, "{rgb}-> %d\n", rgb);
	}
	if (c_or_g == C)
	{
		dprintf(2, "[value: %d]\n", value);
		if(rgb == R)
		{
			data->color->c_r = value;
			dprintf(2, "[value c_r: %d]\n", data->color->c_r);
		}
		else if(rgb == G)
			data->color->c_g = value;
		else
			data->color->c_b = value;
		dprintf(2, "{rgb}-> %d\n", rgb);
	}
}

void	check_convert(t_data *data, char *str, int c_or_g, int rgb)
{
	int	i;
	int	value;

	i = ZERO_INIT;
	value = ZERO_INIT;
	while(str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		error_atoi(data, "Error while atoi!");
	dprintf(2, "STR[i]-> %s\n", str);
	value = ft_atoi(str);
	if (value < 0 || value > 255)
		error_atoi(data, "Color value must be between 0 and 255!");
	else
	{
		dprintf(2, "NBR-> %d\n", value);
		set_value_settings(data, value, c_or_g, rgb);
	}
}

void	set_value(t_data *data, char **split, int c_or_g)
{
	int	i;
	// int	j;
		
	i = 1;
	// j = ZERO_INIT;
	//print_split(split);
	while(split[i])
	{
		data->file->value = ft_split(split[i], ',');
		if (!data->file->value)
			error_split_value(data, "Error while splitting value!");
		check_convert(data, data->file->value[0], c_or_g, (i - 1));
		// dprintf(2, "ICI!\n");
		free_split(data->file->value);
		i++;
	}
}
