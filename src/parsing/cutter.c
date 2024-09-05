/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:10:18 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/05 18:21:59 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int	detect_data(t_data *data, char *str)
{
	(void)data;
	if (ft_strncmp(str, "F", 2) == 0)
		return(F);
	if (ft_strncmp(str, "C", 2) == 0)
		return(C);
	if (ft_strncmp(str, "EA", 3) == 0)
		return(EA);
	if (ft_strncmp(str, "NO", 3) == 0)
		return(NO);
	if (ft_strncmp(str, "WE", 3) == 0)
		return(WE);
	if (ft_strncmp(str, "SO", 3) == 0)
		return(SO);
	else
		return (-1);
}

int	extract_settings(t_data *data)
{
	int	i;
	int	j;
	int end_settings;
	
	i = ZERO_INIT;
	j = ZERO_INIT;
	end_settings = ZERO_INIT;
	while(data->file->tab_data[i][j] != '1')
	{
		j = 0;
		while(data->file->tab_data[i][j] == ' ' || data->file->tab_data[i][j] == '\t')
			j++;
		if (data->file->tab_data[i][j] != '1')
			i++;
	}
	end_settings = i - 1;
	return (end_settings);
}

void	extract_data(t_data *data)
{
	char	**split_settings;
	int	end_settings;
	int	i;
	int	j;
	
	i = ZERO_INIT;
	j = ZERO_INIT;
	end_settings = ZERO_INIT;
	split_settings = NULL;
	end_settings = extract_settings(data);
	while(data->file->tab_data[i] && i <= end_settings)
	{
		while(data->file->tab_data[i][j] == ' ' || data->file->tab_data[i][j] == '\t')
			j++;
		split_settings = ft_split(data->file->tab_data[i], ' ');
		if (!split_settings)
			error_split_sett(data);
		int k = 0;
		while(split_settings[k])
		{
			//printf("[%s]\n", split_settings[k]);
			if(detect_data(data, split_settings[k]) == F) // || == C
			{
				printf("OK\n");
				set_value(data, split_settings, detect_data(data, split_settings[k]));
			}
			k++;
		}
		printf("--\n");
		i++;
		free_split(split_settings);
	}
	printf("final R | - | -: %d\n", data->color->f_r);
	printf("final - | G | -: %d\n", data->color->f_g);
	printf("final - | - | -: %d\n", data->color->f_b);
}

void	check_order_data(t_data *data)
{
	int	i;
	int	j;
	char	comp;
	
	i = ZERO_INIT;
	j = ZERO_INIT;
	while(data->file->tab_data[i][j] == ' ' || data->file->tab_data[i][j] == '\t')
		j++;
	comp = data->file->tab_data[i][j];
	//dprintf(2, "TOP ->[%c]\n", comp);
	if (comp != 'N' && comp != 'S' && comp != 'W' && comp != 'E' && comp != 'F' && comp != 'C')
			error_order(data);
	//dprintf(2, "\033[32mSeems good...\033[0m\n");
}

void	file_cutter(t_data *data)
{
	int	i;
	
	i = ZERO_INIT;
	data->file->tab_data = ft_split(data->file->map_line_cpy, '\n');
	if (!data->file->tab_data)
		error_split(data);
	while(data->file->tab_data[i])
	{
		printf("[%s]\n", data->file->tab_data[i]);
		i++;
	}
	check_order_data(data);
	extract_data(data);
}