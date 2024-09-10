/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:17:15 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/10 17:54:31 by cyferrei         ###   ########.fr       */
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
		printf("Element [%d]: [%s]\n", i, split[i]);
		i++;
	}
}

void	check_syntax(t_data *data, char **split)
{
	int	i;
	int	j;

	(void)data;
	i = 1;
	j = ZERO_INIT;
	while (split[i])
	{
		dprintf(2, "{split[%d][%s]}\n", i, split[i]);
		// dprintf(2, "ICI-> %s\n", split[4]);
		// dprintf(2, "ICI-> %d\n", ft_strlen(split[4]));
		// if (ft_strlen(split[2]) != 1 || ft_strlen(split[4]) != 1)
		// {
		// 	free_split(data->file->split_settings);
		// 	error_order(data, "Syntax error!");
		// }
		// // dprintf(2, "[%s]\n", split[i]);
		// // j = 0;
		// // while (split[i][j] >= '0' && split[i][j] <= '9')
		// // 	j++;
		// // if (split[i][j] == '\0')
		// // 	break ;
		// // if (split[i][j] == ' ' || split[i][j] == '\t')
		// // {
		// // 	while (split[i][j] && (split[i][j] == ' ' || split[i][j] == '\t'))
		// // 		j++;
		// // }
		// // if (split[i][j] != ',')
		// // {
		// // 	free_split(data->file->split_settings);
		// // 	error_order(data, "Syntax error!");
		// // }
		// // j++;
		// // if (split[i][j] != '\0')
		// // {
		// // 	dprintf(2, "ERROR SYNTAX!\n");
		// // 	exit(1);
		// // 	// error
		// // }
		i++;
	}
}

void	check_nb_colors(t_data *data, char **split)
{
	int	i;
	int count;

	i = ZERO_INIT;
	count = ZERO_INIT;
	while (split[i])
	{
		//dprintf(2, "[%s]\n", split[i]);
		if(split[i][0] != ',')
			count++;
		i++;
	}
	if (count != 4)
		error_split_value(data, "Not a valid format for color!");
}

void	set_color_settings(t_data *data, int value, int c_or_g, int rgb)
{
	if (c_or_g == F && data->color->f_set == 0)
	{
		if (rgb == R)
			data->color->f_r = value;
		else if (rgb == G)
			data->color->f_g = value;
		else
			data->color->f_b = value;
		if (rgb == 2)
			data->color->f_set = 1;
	}
	if (c_or_g == C && data->color->c_set == 0)
	{
		if (rgb == R)
			data->color->c_r = value;
		else if (rgb == G)
			data->color->c_g = value;
		else
			data->color->c_b = value;
		if (rgb == 2)
			data->color->c_set = 1;
	}
}

void	check_color(t_data *data, char *str, int c_or_g, int rgb)
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
		set_color_settings(data, value, c_or_g, rgb);
}

void	set_color(t_data *data, char **split, int c_or_g)
{
	int	i;

	i = 1;
	check_nb_colors(data, split);
	//print_split(data->file->split_settings);
	check_syntax(data, data->file->split_settings);
	while (split[i])
	{
		if(split[i][0] == ',')
		{
			i++;
			break;
		}
		data->file->value = ft_split(split[i], ' ');
		if (!data->file->value)
			error_split_value(data, "Error while splitting value!");
		check_color(data, data->file->value[0], c_or_g, (i - 1));
		free_split(data->file->value);
		i++;
	}
}
