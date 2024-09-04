/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:53:06 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/03 13:32:40 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_cub3D.h"

void	print_out(unsigned int nb)
{
	if (nb > 9)
		print_out(nb / 10);
	if (nb <= 9)
	{
		ft_putchar_fd((nb + 48), 1);
		return ;
	}
	ft_putchar_fd((nb % 10 + 48), 1);
}

int	print_unsigned(unsigned int nb)
{
	unsigned int	len;

	print_out(nb);
	len = 1;
	while (nb > 9)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}
/*int main(void)
{
    unsigned int test_value = 12345; // ici votre valeur de test

    printf("\nOutput of print_unsigned: %d\n", print_unsigned(test_value));

    return 0;
}*/