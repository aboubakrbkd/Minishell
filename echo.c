/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:40:25 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/16 17:26:23 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_flag(char *argv)
{
	int	i;

	i = 0;
	if (!ft_strcmp(argv, "-n"))
		return (0);
	if (argv[0] != '-')
		return (1);
	i++;
	while (argv[i])
	{
		if (argv[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	print_arguments(char **argv, int start)
{
	int	i;

	i = start;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
}

int	echo(char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (argv[i] == NULL)
	{
		printf("\n");
		return (0);
	}
	if (ft_strcmp(argv[i], "-") == 0)
	{
		printf("%s", argv[i]);
		printf(" ");
		i++;
	}
	while (argv[i] && !check_if_flag(argv[i]))
	{
		flag = 1;
		i++;
	}
	print_arguments(argv, i);
	if (!flag)
		printf("\n");
	return (0);
}
