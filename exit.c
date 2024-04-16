/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:07:53 by aboukdid          #+#    #+#             */
/*   Updated: 2024/04/16 14:23:29 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

int	is_all_num(char *s)
{
	while (s)
	{
		if (!isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int	exit_function(char **argv)
{
	printf("exit\n");
	if (argv[1] == NULL)
		exit(1);
	if (!is_all_num(argv[1]))
	{
		if (argv[2] == NULL)
			exit(atoi(argv[1]));
		else
			printf("too many arguments\n");
	}
	else
	{
		printf("%s: %s: numeric argument required\n", argv[0], argv[1]);
		exit(255);
	}
	return (0);
}

// int	main(int argc,char **argv, char **envp)
// {
// 	exit_function(argv);
// }
