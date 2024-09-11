/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyprien <cyprien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:28:35 by cyprien           #+#    #+#             */
/*   Updated: 2024/09/11 19:25:00 by cyprien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int ft_isdigit(char c)
{
    if(c >= '0' && c <= '9')
        return(1);
    return (0);
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
        dprintf(2, "ERROR SYNTAX");
        exit(1);
        //error;
    }
    // print_split(tmp);
    free_split(tmp);
    free(cpy);
}