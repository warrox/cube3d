/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:49:45 by cyprien           #+#    #+#             */
/*   Updated: 2024/09/12 16:55:39 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int identify_info(t_data *data, char *infos)
{
    int id_info;
    char    **tmp;

    tmp = ft_split(infos, ' ');
    if (!tmp)
        error_malloc_tmp(data, "Fail to malloc tmp data tab!");
    id_info = ZERO_INIT;
    if (ft_strncmp(tmp[0], "F", 2) == 0)
        id_info = COLOR;
    else if (ft_strncmp(tmp[0], "C", 2) == 0)
        id_info = COLOR;
    else if(ft_strncmp(tmp[0], "EA", 3) == 0)
        id_info = PATH;
    else if (ft_strncmp(tmp[0], "NO", 3) == 0)
        id_info = PATH;
    else if (ft_strncmp(tmp[0], "WE", 3) == 0)
        id_info = PATH;
    else if (ft_strncmp(tmp[0], "SO", 3) == 0)
            id_info = PATH;
    free_split(tmp);
    return (id_info);
}

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
            error_malloc_tmp(data, "Fail to malloc tmp data tab!");
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
            free_split(tmp);
            error_unexpected_info(data, "Unexpected data!");
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
    int i;
    int id_info;

    id_info = ZERO_INIT;
    i = ZERO_INIT;
    if(!check_required_data(data, data->file->infos))
        error_data_format(data, "Missing or extra data detected!");
    while(i < data->file->line_data)
    {
        id_info = identify_info(data, data->file->infos[i]);
        if(id_info == COLOR)
            color_case(data, data->file->infos[i]);
        else if(id_info == PATH)
            path_case(data, data->file->infos[i]);
        i++;
    }
    //print_final_datas(data);
}
