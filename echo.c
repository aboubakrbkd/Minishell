/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:40:25 by aboukdid          #+#    #+#             */
/*   Updated: 2024/06/03 00:18:01 by aboukdid         ###   ########.fr       */
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

int	print_arguments(char **argv, int start, int outfile)
{
	int	i;

	i = start;
	while (argv[i])
	{
		if (!ft_strcmp(argv[i], "?"))
		{
			ft_putnbr_fd(exit_status(0, 0), outfile);
			ft_putchar_fd('\n', outfile);
			exit_status(0, 1);
			return (0);
		}
		write(outfile, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(outfile, " ", 1);
		i++;
	}
	return (1);
}

int	echo(char **argv, int outfile)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (argv[i] == NULL)
	{
		write(outfile, "\n", 1);
		return (0);
	}
	if (ft_strcmp(argv[i], "-") == 0)
	{
		write(outfile, argv[i], ft_strlen(argv[i]));
		write(outfile, " ", 1);
		i++;
	}
	while (argv[i] && !check_if_flag(argv[i]))
	{
		flag = 1;
		i++;
	}
	if (print_arguments(argv, i, outfile) == 0)
		return (0);
	if (!flag)
		write(outfile, "\n", 2);
	exit_status(0, 1);
	return (0);
}
