/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:14:46 by mkimdil           #+#    #+#             */
/*   Updated: 2024/05/17 17:41:56 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	change_to_garb(char *line)
{
	int		i;
	int		tr;
	char	curr_quote;

	i = 0;
	tr = 0;
	curr_quote = '\0';
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"') && tr == 0)
		{
			tr = 1;
			curr_quote = line[i];
		}
		else if (line[i] == curr_quote && tr == 1)
		{
			tr = 0;
			curr_quote = '\0';
		}
		else if (tr == 1)
			line[i] = line[i] * - 1;
		i++;
	}
}

int main()
{
    char ptr[] = "hello world 'this is mouad kimdil'.";
    change_to_garb(ptr);
    printf("%s\n", ptr);
    return 0;
}

