/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 01:18:26 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/19 01:48:20 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rm_quote(char *arg)
{
	int		i;
	int		j;
	int		tr;
	char	qoutes;

	i = -1;
	j = 0;
	tr = 0;
	while (arg[++i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
		{
			qoutes = arg[i], tr = 1;
			break ;
		}
	}
	i = -1;
	while (++i < ft_strlen(arg))
	{
		if (arg[i] == qoutes && tr == 1)
		{
			tr = 0;
			continue ;
		}
		if (arg[i] != qoutes)
			arg[j++] = arg[i];
	}
	arg[j] = '\0';
	return (arg);
}
