/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:08:09 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/03 13:32:40 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_cub3D.h"

char	*gnl_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s || s[0] == '\0')
		return (NULL);
	if (c == 0)
		return (s + ft_strlen(s));
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	*gnl_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (dest);
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return ((void *)dest);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*new;

	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	new = (char *)ft_calloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1),
			sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (s2[i])
	{
		new[j] = s2[i];
		j++;
		i++;
	}
	free((void *)s1);
	return (new);
}

void	*gnl_calloc(size_t nmeb, size_t size)
{
	char	*res;
	char	*str;
	size_t	i;

	res = malloc(nmeb * size);
	if (!res)
		return (NULL);
	str = res;
	i = 0;
	while (i < nmeb * size)
	{
		str[i] = '\0';
		i++;
	}
	return (res);
}
