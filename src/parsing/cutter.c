/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:10:18 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/09 13:05:53 by cyferrei         ###   ########.fr       */
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
	int	end_settings;
	int	i;
	int	j;
	int	k;
	
	i = ZERO_INIT;
	j = ZERO_INIT;
	k = ZERO_INIT;
	end_settings = ZERO_INIT;
	end_settings = extract_settings(data);
	while(data->file->tab_data[i] && i <= end_settings)
	{
		j = 0;
		k = 0;
		while(data->file->tab_data[i][j] == ' ' || data->file->tab_data[i][j] == '\t')
			j++;
		data->file->split_settings = ft_split(data->file->tab_data[i], ' ');
		if (!data->file->split_settings)
			error_order(data);
		while(data->file->split_settings[k])
		{
			if(detect_data(data, data->file->split_settings[k]) == F || detect_data(data, data->file->split_settings[k]) == C)
			{
				dprintf(2, "ICI-> COLOR DETETECTED %d\n", detect_data(data, data->file->split_settings[k]));
				set_value(data, data->file->split_settings, detect_data(data, data->file->split_settings[k]));
				break;
			}
			// this part is for tests
			else if(detect_data(data, data->file->split_settings[k]) == EA || detect_data(data, data->file->split_settings[k]) == NO || detect_data(data, data->file->split_settings[k]) == WE || detect_data(data, data->file->split_settings[k]) == SO)
			{
				dprintf(2, "ICI-> PATH DETETECTED %d\n", detect_data(data, data->file->split_settings[k]));
				break;
			}
			else
			{
				dprintf(2, "ICI_> %s\n", data->file->split_settings[k]);
				printf("ERROR!!!!\n");
				//exit(1);	need to dreate function for exit;
				//also need to check inside syntax and if no re assignation !
			}
			k++;
		}
		i++;
		free_split(data->file->split_settings);
	}
	printf("\nfinalF R | - | -: %d\n", data->color->f_r);
	printf("finalF - | G | -: %d\n", data->color->f_g);
	printf("finalF - | - | B: %d\n", data->color->f_b);
	printf("finalC R | - | -: %d\n", data->color->c_r);
	printf("finalC - | G | -: %d\n", data->color->c_g);
	printf("finalC - | - | B: %d\n", data->color->c_b);
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
	if (comp != 'N' && comp != 'S' && comp != 'W' && comp != 'E' && comp != 'F' && comp != 'C')
			error_order(data);
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