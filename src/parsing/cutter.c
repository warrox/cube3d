/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyprien <cyprien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:10:18 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/11 15:44:24 by cyprien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

// int	detect_data(t_data *data, char *str)
// {
// 	(void)data;
// 	if (ft_strncmp(str, "F", 2) == 0)
// 		return (F);
// 	if (ft_strncmp(str, "C", 2) == 0)
// 		return (C);
// 	if (ft_strncmp(str, "EA", 3) == 0)
// 		return (EA);
// 	if (ft_strncmp(str, "NO", 3) == 0)
// 		return (NO);
// 	if (ft_strncmp(str, "WE", 3) == 0)
// 		return (WE);
// 	if (ft_strncmp(str, "SO", 3) == 0)
// 		return (SO);
// 	else
// 		return (-1);
// }

// int	extract_end_settings(t_data *data)
// {
// 	int	i;
// 	int	j;
// 	int	end_settings;

// 	i = ZERO_INIT;
// 	j = ZERO_INIT;
// 	end_settings = ZERO_INIT;
// 	while (data->file->tab_data[i][j] != '1')
// 	{
// 		j = 0;
// 		while (data->file->tab_data[i][j] == ' '
// 			|| data->file->tab_data[i][j] == '\t')
// 			j++;
// 		if (data->file->tab_data[i][j] != '1')
// 			i++;
// 	}
// 	end_settings = i - 1;
// 	return (end_settings);
// }

// void	extract_data(t_data *data)
// {
// 	int	i;
// 	// int	j;
// 	// int	k;
// 	// int	var;

// 	i = ZERO_INIT;
// 	var = ZERO_INIT;
// 	while (data->file->tab_data[i] && i <= data->file->end_settings)
// 	{
// 		j = 0;
// 		k = 0;
// 		init_detector(data, i, j);
// 		print_split(data->file->value);
// 		// while (data->file->split_settings[k])
// 		// {
// 		// 	var = detect_data(data, data->file->split_settings[k]);
// 		// 	count_data(data, data->file->split_settings[k]);
// 		// 	if (data_detector(data, var))
// 		// 		break ;
// 		// 	k++;
// 		// }
// 		i++;
// 		free_split(data->file->split_settings);
// 	}
// 	check_duplicate(data);
// }

// void	check_order_data(t_data *data)
// {
// 	int		i;
// 	int		j;
// 	char	comp;

// 	i = ZERO_INIT;
// 	j = ZERO_INIT;
// 	while (data->file->tab_data[i][j] == ' '
// 		|| data->file->tab_data[i][j] == '\t')
// 		j++;
// 	comp = data->file->tab_data[i][j];
// 	if (comp != 'N' && comp != 'S' && comp != 'W' && comp != 'E' && comp != 'F'
// 		&& comp != 'C')
// 		error_order(data, "Error with order!");
// }

// // void	check_value_colors(char **value)
// // {
// // 	int	i;
// // 	int	nbr;
	
// // 	i = ZERO_INIT;
// // 	nbr = ZERO_INIT;
// // 	while(value[i])
// // 	{
// // 		nbr = ft_atoi()
// // 	}
// // }

// void	check_args_colors(char **settings)
// {
// 	int	i;
// 	int	j;
// 	int	count;
// 	int	comma;

// 	comma = ZERO_INIT;
// 	count = ZERO_INIT;
// 	j = ZERO_INIT;
// 	i = ZERO_INIT;
// 	while(settings[count])
// 		count++;
// 	dprintf(2, "%d\n", count);
// 	if (count != 3)
// 	{
// 		exit(1);
// 		//error
// 	}
// 	while(settings[i])
// 	{
// 		while(settings[i][j])
// 		{
// 			if (settings[i][j] == ',')
// 				comma++;
// 			j++;
// 		}
// 		if (comma != 2)
// 			exit(1);
// 			//error
// 		i++;
// 		comma = 0;
// 	}
// }

// void	case_color(t_data *data, char **tab, int i)
// {
// 	int	j;

// 	j = ZERO_INIT;
// 	data->file->split_settings = ft_split(tab[i], ',');
// 	if (!data->file->split_settings)
// 	{
// 		exit(1);
// 		// error
// 	}
// 	print_split(data->file->split_settings);
// 	check_args_colors(data->file->split_settings);
// 	while(data->file->split_settings[j])
// 	{
// 		data->file->value = ft_split(data->file->split_settings[j], ' ');
// 		print_split(data->file->value);
// 		free_split(data->file->value);
// 		j++;
// 	}
// 	free_split(data->file->split_settings);	
// }

// void	check_requiered_data(t_data *data, char **tab)
// {
// 	int	i;
// 	int	j;
	
// 	i = ZERO_INIT;
// 	j = ZERO_INIT;
// 	data->file->end_settings = extract_end_settings(data);
// 	while(tab[i] && i <= data->file->end_settings)
// 	{
// 		if (ft_strncmp(tab[i], "F ", 2) == 0 || ft_strncmp(tab[i], "C ", 2) == 0)
// 		{
// 			case_color(data, tab, i);
// 			// COLORS
// 			// data->file->split_settings = ft_split(tab[i], ',');
// 			// if (!data->file->split_settings)
// 			// {
// 			// 	exit(1);
// 			// 	// error
// 			// }
// 			// print_split(data->file->split_settings);
// 			// free_split(data->file->split_settings);	
// 		}
// 		i++;
// 	}
// }

void	check_order(t_data *data)
{
	int	i;
	char	*str;
	
	i = ZERO_INIT;
	str = data->file->map_line_cpy;
	//dprintf(2, "line_in_map: %s\n", data->file->map_line_cpy);
	while(str[i])
		i++;
	i--;
	if (str[i] != '1')
	{
		dprintf(2, "Error order: map is not last!\n");
		exit(1);
		// error;
	}
	i = 0;
	while(str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == 'F' || str[i] == 'C' || str[i] == 'E' || str[i] == 'N'|| str[i] == 'W'|| str[i] == 'S')
		return;
	else
	{
		dprintf(2, "Error order: not expected format data!\n");
		exit(1);
		// error;
	}
}

int	is_map_line(char *line)
{
	int	i;

	i = ZERO_INIT;
	while(line[i] == ' ' || line[i] == 't')
		i++;
	if(line[i] == '1')
		return (1);
	return (0);
}

void	split_data_map(t_data *data)
{
	int	i;
	int	map_idx;
	int	data_idx;
	
	map_idx = ZERO_INIT;
	data_idx = ZERO_INIT;
	i = ZERO_INIT;
	data->file->map = malloc(sizeof(char *) * data->file->line_map);
	if(!data->file->map)
	{
		exit (1);
		// error;
	}
	data->file->infos = malloc(sizeof(char *) * data->file->line_data);
	if(!data->file->infos)
	{
		exit (1);
		// error;
	}
	while(i < data->file->total_line)
	{
		if(is_map_line(data->file->tab_data[i]))
			data->file->map[map_idx++] = ft_strdup(data->file->tab_data[i]);
		else
			data->file->infos[data_idx++] = ft_strdup(data->file->tab_data[i]);
		i++;
	}
}

void	count_line(t_data *data)
{
	int	i;

	i = ZERO_INIT;
	while(data->file->tab_data[i])
		i++;
	data->file->total_line = i;
	i = 0;
	while(i < data->file->total_line)
	{
		if(is_map_line(data->file->tab_data[i]))
			data->file->line_map++;
		else
			data->file->line_data++;
		i++;
	}
	// dprintf(2, "[%d][%s]\n", i, data->file->tab_data[i]);
}

void	file_cutter(t_data *data)
{
	data->file->tab_data = ft_split(data->file->map_line_cpy, '\n');
	if (!data->file->tab_data)
		error_split(data);
	print_split(data->file->tab_data);
	count_line(data);
	split_data_map(data);
	check_order(data);
	// dprintf(2, "[line_map[%d]] | line_data[%d]\n", data->file->line_map, data->file->line_data);
	// check_requiered_data(data, data->file->tab_data);
	// extract_data(data);
	// check_order_data(data);
}
