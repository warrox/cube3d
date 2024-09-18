/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:43:10 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/10 14:35:58 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_cub3D.h"

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length && first[i] != '\0' && second[i] != '\0')
	{
		if ((unsigned char)first[i] > (unsigned char)second[i])
			return (1);
		else if ((unsigned char)first[i] < (unsigned char)second[i])
			return (-1);
		i++;
	}
	if (i == length || (first[i] == '\0' && second[i] == '\0'))
		return (0);
	else if (first[i] == '\0')
		return (-1);
	else
		return (1);
}
