/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:17:15 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/24 10:41:18 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	find_max_len(t_data *data, char *line)
{
	int	line_len;

	line_len = ft_strlen(line);
	if (line_len > data->file->max_len)
		data->file->max_len = line_len;
}

void	fill_map(t_data *data, char *line, char **cpy)
{
	int i;
	int j;

	i = 0;
	j = 0;
	*cpy = malloc(sizeof(char) * (data->file->max_len + 1));
	if (!*cpy)
	{
		// Gérer l'erreur si l'allocation échoue
		exit(1);
	}
	while (line[i])
		(*cpy)[j++] = line[i++];
	while (j < data->file->max_len)
		(*cpy)[j++] = '1';
	(*cpy)[j] = '\0';
}

void	checker_map(t_data *data, char *str)
{
	int	i;

	i = ZERO_INIT;
	while (str[i])
	{
		while (str[i] != '\n')
			i++;
		i++;
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '1')
			break ;
		i++;
	}
	while (str[i])
	{
		if (str[i] == '\n' && !is_wrong_line(&str[i]))
			error_split(data, "Error with the map (space)!");
		if (str[i] == '\n')
		{
			while (str[i] == ' ' || str[i] == '\t')
				i++;
		}
		i++;
	}
}

int	is_wrong_line(char *str)
{
	int	i;

	i = ZERO_INIT;
	str++;
	while (str[i] && ft_strchr(" \t", str[i]))
		i++;
	if (!str[i] || str[i] == '1')
		return (1);
	return (0);
}

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

void	print_file(t_data *data)
{
	print_split(data->file->tab_data);
}

void	print_final_datas(t_data *data)
{
	int i;

	i = ZERO_INIT;
	dprintf(2, "-----------FILE BEFORE PARSING-----------\n\n");
	print_file(data);
	dprintf(2, "\n");
	dprintf(2, "-----------FINALS DATA-----------\n");
	dprintf(2, "final_F_r: %d\n", data->file->color->f_r);
	dprintf(2, "final_F_g: %d\n", data->file->color->f_g);
	dprintf(2, "final_F_b: %d\n", data->file->color->f_b);
	dprintf(2, "final_C_r: %d\n", data->file->color->c_r);
	dprintf(2, "final_C_g: %d\n", data->file->color->c_g);
	dprintf(2, "final_C_b: %d\n", data->file->color->c_b);
	dprintf(2, "----------------------------------------\n");
	dprintf(2, "final_path_NO: %s\n", data->file->path->path_no);
	dprintf(2, "final_path_WE: %s\n", data->file->path->path_we);
	dprintf(2, "final_path_EA: %s\n", data->file->path->path_ea);
	dprintf(2, "final_path_SO: %s\n", data->file->path->path_so);
	dprintf(2, "----------------------------------------\n");
	dprintf(2, "final_orientation: %c\n\n", data->file->orientation);
	dprintf(2, "-----------FINALS MAP-----------\n");
	while(i < data->file->line_map)
	{
		dprintf(2, "%s\n", data->file->map[i]);
		i++;
	}
	dprintf(2, "----------------------------------------\n");
}
