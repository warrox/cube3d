/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:26:34 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/03 13:32:40 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_cub3D.h"

static int	ft_type(const char *input, va_list args)
{
	int	i;

	i = 0;
	if (*input == 'c')
		i += print_char(va_arg(args, int));
	else if (*input == 's')
		i += print_string(va_arg(args, char *));
	else if (*input == 'p')
		i += print_pointer(va_arg(args, unsigned long long));
	else if (*input == 'd' || *input == 'i')
		i += print_int(va_arg(args, int));
	else if (*input == 'u')
		i += print_unsigned(va_arg(args, unsigned int));
	else if (*input == 'x' || *input == 'X')
		i += print_hexa(va_arg(args, unsigned int), *input);
	else if (*input == '%')
		i += print_percent();
	return (i);
}

int	ft_printf(const char *input, ...)
{
	va_list	args;
	int		i;
	int		total_len;

	i = 0;
	total_len = 0;
	va_start(args, input);
	if (input == NULL)
		return (-1);
	while (input[i])
	{
		if (input[i] == '%')
		{
			total_len += ft_type(&input[i + 1], args);
			i++;
		}
		else
			total_len += print_char(input[i]);
		i++;
	}
	va_end(args);
	return (total_len);
}
/*int main(void)
{
	int nb;
	int nb2 = -5;
	int nb3 = 2564;
	nb = -2147483648;
	char c;
	c = 55;
	char *str1 = "Salut les amis";
	char *str2 = NULL;
	int nb_hex = 2147483647;
	int nb_unsigned = -2;
	int *ptr_nb2 = &nb2;
	int *ptr_nb3 = &nb3;
	ptr_nb3 = NULL;

	printf("Total : %d\n",
		ft_printf("Resultat de la fonction : [%c] [%d] [%s] [%s] [%x] [%X] [%u]\n",
			c, nb, str1, str2, nb_hex, nb_hex, nb_unsigned));
	printf("Total : %d\n",
		printf("Resultat de la fonction : [%c] [%d] [%s] [%s] [%x] [%X] [%u]\n",
			c, nb, str1, str2, nb_hex, nb_hex, nb_unsigned));

	printf("Total : %d\n",
		ft_printf("Resultat de la fonction : [%p] [%p] [%p]\n", ptr_nb2,
			ptr_nb3, NULL));
	printf("Total : %d\n", printf("Resultat de la fonction : [%p] [%p] [%p]\n",
			ptr_nb2, ptr_nb3, NULL));

	printf("Resultat attendu : %d || ", printf(NULL));
	printf("Resultat de ft_printf : %d\n", ft_printf(NULL));

		printf("%s\n", "%");
	ft_printf("%s\n", "%");
	printf("%d\n", ft_printf(0));
	ft_printf("%d\n", ft_printf(0));


	return(0);
}*/