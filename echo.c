/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:40:25 by aboukdid          #+#    #+#             */
/*   Updated: 2024/04/15 09:56:33 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (argv[i] == NULL)
	{
		printf("\n");
		return (0) ;
	}
	while (argv[i] && !ft_strncmp(argv[i], "-n", 2))
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