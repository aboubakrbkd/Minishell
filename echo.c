/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:40:25 by aboukdid          #+#    #+#             */
/*   Updated: 2024/08/04 17:58:37 by aboukdid         ###   ########.fr       */
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

int	print_arguments(char **argv, int start)
{
	int	i;

	i = start;
	while (argv[i])
	{
		if (!ft_strcmp(argv[i], "?"))
		{
			ft_putnbr_fd(ex_st(0, 0), 1);
			ft_putchar_fd('\n', 1);
			ex_st(0, 1);
			return (0);
		}
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	return (1);
}

int	checking_null(char **argv)
{
	if (*argv == NULL)
	{
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}

int	echo(char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (checking_null(argv))
		return (0);
	if (ft_strcmp(argv[i], "-") == 0)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		write(1, " ", 1);
		i++;
	}
	while (argv[i] && !check_if_flag(argv[i]))
	{
		flag = 1;
		i++;
	}
	if (print_arguments(argv, i) == 0)
		return (0);
	if (!flag)
		write(1, "\n", 1);
	return (0);
}
