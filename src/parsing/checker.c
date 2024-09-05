/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:03:29 by cyferrei          #+#    #+#             */
/*   Updated: 2024/09/05 10:15:54 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_lib.h"

void	check_envp(char **envp)
{
	if (!*envp)
		error_msg("No environment variable!");
}

void	check_nb_args(int argc)
{
	if (argc != 2)
		error_msg("2 args needed!");
}

int	ft_count_char(char *argv, char c)
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
	if (ft_count_char(argv[1], '.') != 1)
		error_msg("File needs to be in .cub!");
	str = ft_strrchr(argv[1], '.');
	if (str)
	{
		if (ft_strcmp(str, ".cub") != 0)
			error_msg("File needs to be in .cub!");
	}
}

void	checker(int argc, char **argv, char **envp)
{
	check_envp(envp);
	check_nb_args(argc);
	check_extension(argv);
}
