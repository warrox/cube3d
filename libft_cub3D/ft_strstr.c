/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:24:18 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/03 13:32:40 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_cub3D.h"

char	*ft_strstr(char *haystack, char *needle)
{
	size_t	haystack_len;
	size_t	needle_len;
	size_t	i;
	size_t	j;

	haystack_len = ft_strlen(haystack);
	needle_len = ft_strlen(needle);
	i = 0;
	while (i <= haystack_len - needle_len)
	{
		j = 0;
		while (j < needle_len)
		{
			if (haystack[i + j] != needle[j])
				break ;
			j++;
		}
		if (j == needle_len)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
