/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:28:35 by cyprien           #+#    #+#             */
/*   Updated: 2024/09/12 15:24:12 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void    set_value(t_data *data, char *str, char **split)
{
    char    **tmp;
    char    **tmp_value;
    int id_value;

    id_value = ZERO_INIT;
    tmp = NULL;
    tmp_value = NULL;
    tmp = ft_split(str, ' ');
    if(!tmp)
        error_malloc_value(data, str, split, "Fail to malloc tmp (in set_value)!");
    tmp_value = ft_split(tmp[1], ',');
    if (!tmp_value)
    {
        free_split(tmp);
        error_malloc_value(data, str, split, "Fail to malloc tmp_value (in set_value)!");
    }
    if(ft_strncmp(tmp[0], "F", 2) == 0)
        id_value = F;
    else
        id_value = C;
    if(id_value == F)
    {
        data->file->color->f_r = ft_atoi(tmp_value[0]);
        data->file->color->f_g = ft_atoi(tmp_value[1]);
        data->file->color->f_b = ft_atoi(tmp_value[2]);
    }
    else 
    {
        data->file->color->c_r = ft_atoi(tmp_value[0]);
        data->file->color->c_g = ft_atoi(tmp_value[1]);
        data->file->color->c_b = ft_atoi(tmp_value[2]);
    }
    free_split(tmp_value);
    free_split(tmp);
}

int    check_value(t_data *data, char *str, char **split)
{
    char    **tmp;
    char    **tmp_value;
    int value;
    int i;

    tmp = NULL;
    tmp_value = NULL;
    i = 1;
    tmp = ft_split(str, ' ');
    if (!tmp)
        error_malloc_value(data, str, split, "Fail to malloc tmp (in check_value)!");
    tmp_value = ft_split(tmp[1], ',');
    if (!tmp_value)
    {
        free_split(tmp);
        error_malloc_value(data, str, split, "Fail to malloc tmp_value (in check_value)!");
    }
    i = 0;
    while(tmp_value[i])
    {
        value = ft_atoi(tmp_value[i]);
        if (value < 0 || !(value >= 0 && value <= 255))
        {
            free_split(tmp_value);
            free_split(tmp);
            return (0);
        }
        i++;
    }
    free_split(tmp_value);
    free_split(tmp);
    return (1);
}

int check_syntax(char *str)
{
    int i;
    int count;
    
    i = 2;
    count = ZERO_INIT;
    while(str[i])
    {
        if (str[i] == ',')
            count++;
        if (!ft_isdigit(str[i]) && str[i] != ',')
            return (0);
        i++;
    }
    if (count != 2)
        return (0);
    return (1);
}

void    color_case(t_data *data, char *infos)
{
    char    **tmp;
    char    *cpy;
    cpy = clear_whitespace(data, infos);
    tmp = ft_split(infos, ' ');
    if (!tmp)
        error_malloc_value(data, cpy, tmp, "Fail to malloc tmp (in color_case)!");
    if(!check_syntax(cpy))
        error_malloc_value(data, cpy, tmp, "Error syntax detected in colors!");
    if(!check_value(data, cpy, tmp))
        error_malloc_value(data, cpy, tmp, "Error value detected in colors!");
    set_value(data, cpy, tmp);
    free_split(tmp);
    free(cpy);
}