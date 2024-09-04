/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:26:27 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/03 13:32:40 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_cub3D.h"

int	print_int(int nb)
{
	int		len;
	char	*num;

	len = 0;
	num = ft_itoa(nb);
	len = print_string(num);
	free(num);
	return (len);
}

/*int main(void)
{
	int nb = -85;
	printf("%d\n", print_int(nb));
	return(0);
}*/