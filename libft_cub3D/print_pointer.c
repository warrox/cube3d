/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:37:15 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/03 13:32:40 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_cub3D.h"

int	ptr_len(unsigned long long nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		len++;
		nb = nb / 16;
	}
	return (len);
}

void	conv_ptr(unsigned long long nb)
{
	if (nb >= 16)
	{
		conv_ptr(nb / 16);
		conv_ptr(nb % 16);
	}
	else
	{
		if (nb <= 9)
			ft_putchar_fd((nb + '0'), 1);
		else
		{
			ft_putchar_fd((nb - 10 + 'a'), 1);
		}
	}
}

int	print_pointer(unsigned long long ptr)
{
	int	final_len;
	int	ptr_lenght;

	if (ptr == 0)
		return (write(1, "(nil)", 5));
	ptr_lenght = ptr_len(ptr);
	final_len = 0;
	final_len += write(1, "0x", 2);
	if (ptr == 0)
		final_len += write(1, "0", 1);
	else
	{
		conv_ptr(ptr);
	}
	return (final_len + ptr_lenght);
}

/*int	main(void)
{
	unsigned long long test_ptr = 0; // ici votre valeur de test
	printf("\nOutput of print_ptr: %d\n", print_ptr(test_ptr));
	return (0);
}
*/
