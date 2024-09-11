/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyprien <cyprien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:28:35 by cyprien           #+#    #+#             */
/*   Updated: 2024/09/11 21:39:02 by cyprien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void    set_value(t_data *data, char *str)
{
    char    **tmp;
    char    **tmp_value;
    int id_value;

    id_value = ZERO_INIT;
    tmp = NULL;
    tmp_value = NULL;
    tmp = ft_split(str, ' ');
    if(!tmp)
    {
        exit(1);
        // error;
    }
    tmp_value = ft_split(tmp[1], ',');
    if (!tmp_value)
    {
        exit(1);
        // error;
    }
    dprintf(2, "TMP[0]: %s\n", tmp[0]);
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

int    check_value(char *str)
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
    {
        exit(1);
        // error;
    }
    print_split((tmp));
    tmp_value = ft_split(tmp[1], ',');
    if (!tmp_value)
    {
        exit(1);
        // error;
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
    //int i;
    char    **tmp;
    char    *cpy;
    //i = ZERO_INIT;
    cpy = clear_whitespace(infos);
    tmp = ft_split(infos, ' ');
    if (!tmp)
    {
        exit(1);
        //error;
    }
    if(!check_syntax(cpy))
    {
        dprintf(2, "ERROR SYNTAX\n");
        exit(1);
        //error;
    }
    if(!check_value(cpy))
    {
        dprintf(2, "ERROR VALUE\n");
        exit(1);
        // error;
    }
    set_value(data, cpy);
    // print_split(tmp);
    free_split(tmp);
    free(cpy);
}