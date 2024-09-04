/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:50:42 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/03 13:32:40 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_cub3D.h"

int	hexa_len(unsigned int nb)
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

void	conv_hex(unsigned int nb, const char form)
{
	if (nb >= 16)
	{
		conv_hex(nb / 16, form);
		conv_hex(nb % 16, form);
	}
	else
	{
		if (nb <= 9)
			ft_putchar_fd((nb + '0'), 1);
		else
		{
			if (form == 'x')
				ft_putchar_fd((nb - 10 + 'a'), 1);
			if (form == 'X')
				ft_putchar_fd((nb - 10 + 'A'), 1);
		}
	}
}

int	print_hexa(unsigned int nb, const char form)
{
	if (nb == 0)
		return (write(1, "0", 1));
	else
		conv_hex(nb, form);
	return (hexa_len(nb));
}

/*int	main(void)
{
	unsigned int nb;
	nb = -1685;

	printf("%d\n", print_hexa(nb, 'x'));
	printf("%x", nb);
	return (0);
}*/