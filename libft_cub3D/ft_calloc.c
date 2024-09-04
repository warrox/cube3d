/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:09:30 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/03 13:32:40 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_cub3D.h"

void	*ft_calloc(size_t nmeb, size_t size)
{
	void	*result;

	if (nmeb * size == 0)
	{
		result = malloc(0);
		if (!result)
		{
			return (NULL);
		}
		return (result);
	}
	else if (!nmeb || !size || (nmeb * size) / size != nmeb)
	{
		return (NULL);
	}
	result = (char *)malloc(nmeb * size);
	if (!result)
	{
		return (NULL);
	}
	ft_bzero(result, (nmeb * size));
	return (result);
}
