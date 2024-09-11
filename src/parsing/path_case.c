/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyprien <cyprien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:54:11 by cyprien           #+#    #+#             */
/*   Updated: 2024/09/12 00:10:12 by cyprien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int check_extension_path(char *str)
{
    char *tmp;

    tmp = NULL;
    if(ft_strncmp(str, "./", 2) != 0)
        return (0);
    if (ft_count_char(str, '.') != 2)
        return (0);
    tmp = ft_strrchr(str, '.');
    if (str)
    {
        if (ft_strcmp(tmp, ".xpm") != 0)
            return (0);
    }
    return (1);
}

int check_syntax_path(char *str)
{
    int i;
    char **tmp;

    i = ZERO_INIT;
    tmp = NULL;
    tmp = ft_split(str, ' ');
    if (!tmp)
    {
        exit(1);
        // error;
    }
    while(tmp[i])
        i++;
    if (i != 2)
    {
        free_split(tmp);
        return (0);
    }
    free_split(tmp);
    return(1);
}

char    *clear_whitespace_path(char *str)
{
    int i;
    int j;
    int count_char;
    int flag;
    char    *clear_path;

    i = ZERO_INIT;
    j = ZERO_INIT;
    count_char = ZERO_INIT;
    flag = ZERO_INIT;
    clear_path = NULL;
    while(str[i])
    {
        if (str[i] == ' ' || str[i] == '\t')
            i++;
        count_char++;
        i++;
    }
    clear_path = malloc((sizeof(char) * count_char) + 2);
    if (!clear_path)
    {
        exit(1);
        // error;
    }
    i = 0;
    while(str[i])
    {
        while(str[i] == ' ' || str[i] == '\t')
            i++;
        clear_path[j] = str[i];
        flag++;
        if (flag == 2)
        {
            j++;
            clear_path[j] = ' ';
        }
        i++;
        j++;
    }
    clear_path[j] = '\0';
    return (clear_path);
}

void    path_case(t_data *data, char *str)
{
    char    *cpy;
    char    **tmp;

    (void)data;
    cpy = NULL;
    tmp = NULL;
    cpy = clear_whitespace_path(str);
    tmp = ft_split(cpy, ' ');
    if (!tmp)
    {
        exit(1);
        // error;
    }
    if(!check_syntax_path(str))
    {
        dprintf(2, "ERROR IN PATH\n");
        exit(1);
        // error;
    }
    if(!check_extension_path(tmp[1]))
    {
        dprintf(2, "ERROR IN PATH EXTENSION\n");
        exit(1);
        // error;
    }
    dprintf(2, "clear_str: %s\n", cpy);
    free_split(tmp);
    free(cpy);
}