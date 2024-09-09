/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:14:17 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/05 17:57:46 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_cub3D.h"

int	ft_atoi(const char *nbr)
{
	long result;
	long sign;

	sign = 1;
	result = 0;
	while (*nbr && (*nbr == ' ' || (*nbr >= 9 && *nbr <= 13)))
		++nbr;
	if (*nbr && (*nbr == '-' || *nbr == '+'))
	{
		if (*nbr++ == '-')
			sign *= -1;
	}
	while (*nbr && (*nbr >= '0' && *nbr <= '9'))
		result = (*nbr++ - '0') + result * 10;
	return (result * sign);
}