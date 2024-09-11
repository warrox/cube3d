/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyprien <cyprien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:49:45 by cyprien           #+#    #+#             */
/*   Updated: 2024/09/11 16:15:04 by cyprien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int is_all_data(t_data *data)
{
    int all_check;

    all_check = 1;
    if (data->file->color->f_check != 1)
        all_check = 0;
    if (data->file->color->c_check != 1)
        all_check = 0;
    if (data->file->path->ea_check != 1)
        all_check = 0;
    if (data->file->path->no_check != 1)
        all_check = 0;
    if (data->file->path->we_check != 1)
        all_check = 0;
    if (data->file->path->so_check != 1)
        all_check = 0;
    if (all_check)
        return (1);
    return (0);
}

int    check_required_data(t_data *data, char **infos)
{
    int i;
    char    **tmp;
    
    tmp = NULL;
    i = ZERO_INIT;
    while(i < data->file->line_data)
    {
        tmp = ft_split(infos[i], ' ');
        if (!tmp)
        {
            exit(1);
            //error;
        }
        if (ft_strncmp(tmp[0], "F", 2) == 0)
            data->file->color->f_check++;
        else if (ft_strncmp(tmp[0], "C", 2) == 0)
            data->file->color->c_check++;
        else if(ft_strncmp(tmp[0], "EA", 3) == 0)
            data->file->path->ea_check++;
        else if (ft_strncmp(tmp[0], "NO", 3) == 0)
            data->file->path->no_check++;
        else if (ft_strncmp(tmp[0], "WE", 3) == 0)
            data->file->path->we_check++;
        else if (ft_strncmp(tmp[0], "SO", 3) == 0)
            data->file->path->so_check++;
        else
        {
            dprintf(2, "UNEXECPETED DATA\n");
            exit(1);
            free_split(tmp);
            //error
        }
        free_split(tmp);
        i++;
    }
    if (is_all_data(data))
        return(1);
    return(0);
}

void    data_parser(t_data *data)
{
    if(!check_required_data(data, data->file->infos))
        dprintf(2, "TROUBLES DATA HERE\n");
}