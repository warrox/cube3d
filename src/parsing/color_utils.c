/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:18:07 by cyprien           #+#    #+#             */
/*   Updated: 2024/09/16 15:44:54 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*clear_whitespace(t_data *data, char *str)
{
	int		i;
	int		j;
	int		flag;
	char	*clear_cpy;
	int		count_char;

	i = ZERO_INIT;
	flag = 1;
	clear_cpy = NULL;
	count_char = ZERO_INIT;
	j = ZERO_INIT;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		count_char++;
		i++;
	}
	clear_cpy = malloc((sizeof(char) * count_char) + 2);
	if (!clear_cpy)
		error_malloc_whtspc(data, clear_cpy, "Fail to malloc clear_cpy!");
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
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
	return (clear_cpy);
}
