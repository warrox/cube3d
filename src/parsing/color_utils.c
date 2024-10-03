/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:18:07 by cyprien           #+#    #+#             */
/*   Updated: 2024/10/03 12:27:40 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	count_non_whitespace(char *str)
{
	int	i;
	int	count_char;

	i = 0;
	count_char = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			count_char++;
		i++;
	}
	return (count_char);
}

char	*remove_whitespace(t_data *data, char *str, int count_char)
{
	int		i;
	int		j;
	int		flag;
	char	*clear_cpy;

	clear_cpy = malloc((sizeof(char) * (count_char + 2)));
	if (!clear_cpy)
		error_malloc_whtspc(data, clear_cpy, "Fail to malloc clear_cpy!");

	i = 0;
	j = 0;
	flag = 1;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '\0')
			break;
		clear_cpy[j++] = str[i];
		if (flag && str[i] != '\0')
		{
			clear_cpy[j++] = ' ';
			flag = 0;
		}
		i++;
	}
	clear_cpy[j] = '\0';
	return (clear_cpy);
}

char	*clear_whitespace(t_data *data, char *str)
{
	int	count_char;

	count_char = count_non_whitespace(str);
	return (remove_whitespace(data, str, count_char));
}
