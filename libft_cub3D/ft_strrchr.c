/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:00:46 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/03 15:37:03 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_cub3D.h"

char	*ft_strrchr(char *str, int searchedChar)
{
	int	len;

	len = ft_strlen((char *)str);
	while (str[len] != (unsigned char)searchedChar)
	{
		if (len == 0 && str[len] != searchedChar)
			return ((char *)0);
		len--;
	}
	return ((char *)&str[len]);
}
