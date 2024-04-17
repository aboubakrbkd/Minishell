/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:40:25 by aboukdid          #+#    #+#             */
/*   Updated: 2024/04/16 16:49:34 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int	check_if_flag(char *argv)
{
	int i;

	i = 0;
	if (!strcmp(argv, "-n"))
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
	if (strcmp(argv[i], "-") == 0)
	{
        printf("%s", argv[i]);
        i++;
    }
	while (argv[i] && !check_if_flag(argv[i]))
	{
		flag = 1;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	return (0);
}

// int main(int argc, char **argv)
// {
// 	echo(argv);
// }
