/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoutes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:44:40 by mkimdil           #+#    #+#             */
/*   Updated: 2024/05/17 17:46:19 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_double(char *line)
{
	int	i;
	int	tr;

	i = 0;
	tr = 0;
	while (line[i])
	{
		if (line[i] == '\'' && tr == 0)
			tr = 2;
		else if (line[i] == '\'' && tr == 2)
			tr = 0;
		else if (line[i] == '"' && tr == 0)
			tr = 1;
		else if (line[i] == '"' && tr == 1)
			tr = 0;
		i++;
	}
	if (tr == 1 || tr == 2)
		printf("syntax error\n");
}

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
			line[i] = line[i] * -1;
		i++;
	}
}
