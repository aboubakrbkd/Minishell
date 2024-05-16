/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:07:53 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/16 17:29:36 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_all_num(char *s)
{
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
		exit(0);
	if (is_all_num(argv[1]))
	{
		if (argv[2] == NULL)
			exit(ft_atoi(argv[1]));
		else
		{
			printf("too many arguments\n");
			return (1);
		}
	}
	else
	{
		printf("%s: %s: numeric argument required\n", argv[0], argv[1]);
		exit(255);
	}
	return (0);
}
