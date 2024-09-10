/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:10:18 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/10 18:42:13 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int	detect_data(t_data *data, char *str)
{
	(void)data;
	if (ft_strncmp(str, "F", 2) == 0)
		return (F);
	if (ft_strncmp(str, "C", 2) == 0)
		return (C);
	if (ft_strncmp(str, "EA", 3) == 0)
		return (EA);
	if (ft_strncmp(str, "NO", 3) == 0)
		return (NO);
	if (ft_strncmp(str, "WE", 3) == 0)
		return (WE);
	if (ft_strncmp(str, "SO", 3) == 0)
		return (SO);
	else
		return (-1);
}

int	extract_end_settings(t_data *data)
{
	int	i;
	int	j;
	int	end_settings;

	i = ZERO_INIT;
	j = ZERO_INIT;
	end_settings = ZERO_INIT;
	while (data->file->tab_data[i][j] != '1')
	{
		j = 0;
		while (data->file->tab_data[i][j] == ' '
			|| data->file->tab_data[i][j] == '\t')
			j++;
		if (data->file->tab_data[i][j] != '1')
			i++;
	}
	end_settings = i - 1;
	return (end_settings);
}

void	extract_data(t_data *data)
{
	int	i;
	int	j;
	int	k;
	int	var;

	i = ZERO_INIT;
	var = ZERO_INIT;
	while (data->file->tab_data[i] && i <= data->file->end_settings)
	{
		j = 0;
		k = 0;
		init_detector(data, i, j);
		print_split(data->file->value);
		// while (data->file->split_settings[k])
		// {
		// 	var = detect_data(data, data->file->split_settings[k]);
		// 	count_data(data, data->file->split_settings[k]);
		// 	if (data_detector(data, var))
		// 		break ;
		// 	k++;
		// }
		i++;
		free_split(data->file->split_settings);
	}
	check_duplicate(data);
}

void	check_order_data(t_data *data)
{
	int		i;
	int		j;
	char	comp;

	i = ZERO_INIT;
	j = ZERO_INIT;
	while (data->file->tab_data[i][j] == ' '
		|| data->file->tab_data[i][j] == '\t')
		j++;
	comp = data->file->tab_data[i][j];
	if (comp != 'N' && comp != 'S' && comp != 'W' && comp != 'E' && comp != 'F'
		&& comp != 'C')
		error_order(data, "Error with order!");
}

// void	check_value_colors(char **value)
// {
// 	int	i;
// 	int	nbr;
	
// 	i = ZERO_INIT;
// 	nbr = ZERO_INIT;
// 	while(value[i])
// 	{
// 		nbr = ft_atoi()
// 	}
// }

void	check_args_colors(char **settings)
{
	int	i;
	int	j;
	int	count;
	int	comma;

	comma = ZERO_INIT;
	count = ZERO_INIT;
	j = ZERO_INIT;
	i = ZERO_INIT;
	while(settings[count])
		count++;
	dprintf(2, "%d\n", count);
	if (count != 3)
	{
		exit(1);
		//error
	}
	while(settings[i])
	{
		while(settings[i][j])
		{
			if (settings[i][j] == ',')
				comma++;
			j++;
		}
		if (comma != 2)
			exit(1);
			//error
		i++;
		comma = 0;
	}
}

void	case_color(t_data *data, char **tab, int i)
{
	int	j;

	j = ZERO_INIT;
	data->file->split_settings = ft_split(tab[i], ',');
	if (!data->file->split_settings)
	{
		exit(1);
		// error
	}
	print_split(data->file->split_settings);
	check_args_colors(data->file->split_settings);
	while(data->file->split_settings[j])
	{
		data->file->value = ft_split(data->file->split_settings[j], ' ');
		print_split(data->file->value);
		free_split(data->file->value);
		j++;
	}
	free_split(data->file->split_settings);	
}

void	check_requiered_data(t_data *data, char **tab)
{
	int	i;
	int	j;
	
	i = ZERO_INIT;
	j = ZERO_INIT;
	data->file->end_settings = extract_end_settings(data);
	while(tab[i] && i <= data->file->end_settings)
	{
		if (ft_strncmp(tab[i], "F ", 2) == 0 || ft_strncmp(tab[i], "C ", 2) == 0)
		{
			case_color(data, tab, i);
			// COLORS
			// data->file->split_settings = ft_split(tab[i], ',');
			// if (!data->file->split_settings)
			// {
			// 	exit(1);
			// 	// error
			// }
			// print_split(data->file->split_settings);
			// free_split(data->file->split_settings);	
		}
		i++;
	}
}

void	file_cutter(t_data *data)
{
	int	i;

	i = ZERO_INIT;
	data->file->tab_data = ft_split(data->file->map_line_cpy, '\n');
	if (!data->file->tab_data)
		error_split(data);
	print_split(data->file->tab_data);
	check_requiered_data(data, data->file->tab_data);
	// extract_data(data);
	// check_order_data(data);
}
