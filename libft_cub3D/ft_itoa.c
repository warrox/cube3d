/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:12:32 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/03 13:32:40 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_cub3D.h"

static int	ft_len(int nbr)
{
	if (nbr == 0)
		return (0);
	return (1 + ft_len(nbr / 10));
}

static void	write_itoa(char *result, long nb, size_t i)
{
	if (nb == 0)
		return ;
	result[--i] = nb % 10 + '0';
	write_itoa(result, nb / 10, i);
}

char	*ft_itoa(int nbr)
{
	char	*res;
	long	nb;
	int		nega;
	int		len;

	nb = nbr;
	len = 0;
	nega = 0;
	if (nb <= 0)
	{
		nega = 1;
		nb *= -1;
	}
	len += ft_len(nb);
	res = (char *)ft_calloc(len + nega + 1, sizeof(char));
	if (!res)
		return (NULL);
	if (nega == 1)
		res[0] = '-';
	if (nb == 0)
		res[0] = '0';
	write_itoa(&res[nega], nb, len);
	return (res);
}
