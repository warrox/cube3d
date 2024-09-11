/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyprien <cyprien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:28:35 by cyprien           #+#    #+#             */
/*   Updated: 2024/09/11 20:50:05 by cyprien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int ft_isdigit(char c)
{
    if(c >= '0' && c <= '9')
        return(1);
    return (0);
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

char    *clear_whitespace(char *str)
{
    int i;
    int j;
    int flag;
    char    *clear_cpy;
    int count_char;
    
    i = ZERO_INIT;
    flag = 1;
    clear_cpy = NULL;
    count_char = ZERO_INIT;
    j = ZERO_INIT;
    while(str[i])
    {
        if(str[i] == ' '  || str[i] == '\t')
            i++;
        count_char++;
        i++;
    }
    clear_cpy = malloc((sizeof(char) * count_char) + 2);
    if (!clear_cpy)
    {
        exit(1);
        //error;
    }
    i = 0;
    while(str[i])
    {
        while(str[i] == ' '  || str[i] == '\t')
            i++;
        clear_cpy[j] = str[i];
        {
            if (flag)
            {
                j++;
                clear_cpy[j] = ' ';
                flag = 0;
            }
        }
        i++;
        j++;
    }
    clear_cpy[j] = '\0';
    dprintf(2, "[ICI]-> %s\n", clear_cpy);
    return(clear_cpy);
}

void    color_case(char *infos)
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
    // print_split(tmp);
    free_split(tmp);
    free(cpy);
}