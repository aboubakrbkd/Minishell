/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:07:53 by aboukdid          #+#    #+#             */
/*   Updated: 2024/06/03 00:15:48 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_all_num(char *s)
{
	if (*s == '-' || *s == '+')
		s++;
	if (*s == '\0')
		return (0);
	while (*s)
	{
		if (!is_number(*s))
			return (0);
		s++;
	}
	return (1);
}

int	exit_function(char **argv)
{
	printf("exit\n");
	if (argv[1] == NULL)
	{
		exit_status(0, 0);
		exit(0);
	}
	if (is_all_num(argv[1]))
	{
		if (argv[2] == NULL)
		{
			if (ft_atoi(argv[1]) < 0)
			{
				exit_status(256 + ft_atoi(argv[1]), 1);
				exit(256 + ft_atoi(argv[1]));
			}
			else if (ft_atoi(argv[1]) > 255)
			{
				exit_status(ft_atoi(argv[1]) % 256, 1);
				exit(ft_atoi(argv[1]) % 256);
			}
			else
			{
				exit_status(ft_atoi(argv[1]), 1);
				exit(ft_atoi(argv[1]));
			}
		}
		else
		{
			printf("too many arguments\n");
			return (1);
		}
	}
	else
	{
		printf("%s: %s: numeric argument required\n", argv[0], argv[1]);
		exit_status(255, 1);
		exit(255);
	}
	return (0);
}
