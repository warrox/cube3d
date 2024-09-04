/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:03:29 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/04 11:11:35 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	check_envp(char **envp)
{
	if (!*envp)
	{
		printf("\033[31mError\nNo environment variable!\n\033[0m");
		exit(EXIT_FAILURE);
	}
}

void	check_nb_args(int argc)
{
	if (argc != 2)
	{
		printf("\033[31mError\n2 args needed!\n\033[0m");
		exit(EXIT_FAILURE);
	}
}

int	ft_count_dot(char *argv, char c)
{
	int	i;
	int	count;

	i = ZERO_INIT;
	count = ZERO_INIT;
	while (argv[i])
	{
		if (argv[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	check_extension(char **argv)
{
	char	*str;

	str = NULL;
	if (ft_count_dot(argv[1], '.') != 1)
	{
		printf("\033[31mError\nMap needs to be in .cub!\n\033[0m");
		exit(EXIT_FAILURE);
	}
	str = ft_strrchr(argv[1], '.');
	if (str)
	{
		if (ft_strcmp(str, ".cub") != 0)
		{
			printf("\033[31mError\nMap needs to be in .cub!\n\033[0m");
			exit(EXIT_FAILURE);
		}
	}
}

void	checker(int argc, char **argv, char **envp)
{
	check_envp(envp);
	check_nb_args(argc);
	check_extension(argv);
}
