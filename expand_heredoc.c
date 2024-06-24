/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 01:37:05 by mkimdil           #+#    #+#             */
/*   Updated: 2024/06/03 03:20:47 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variables(char *input)
{
	char	*exp;
	char	*name;
	char	*end;
	char	*start;
	char	*dollar;
	char	*var_value;

	exp = malloc(sizeof(char) * 1000);
	name = malloc(sizeof(char) * 1000);
	if (!exp || !name)
		return NULL;
	exp[0] = '\0';
	start = input;
	dollar = ft_strchr(start, '$');
	while (dollar)
	{
		ft_strncat(exp, start, dollar - start);
		if (!ft_isalnum((unsigned char)dollar[1]) && dollar[1] != '_') {
			ft_strncat(exp, dollar, 1);
			start = dollar + 1;
			dollar = ft_strchr(start, '$');
			continue;
		}
		end = dollar + 1;
		while (*end && (ft_isalnum((unsigned char)*end) || *end == '_'))
			end++;
		ft_strncpy(name, dollar + 1, end - dollar - 1);
		name[end - dollar - 1] = '\0';
		var_value = getenv(name);
		if (var_value)
			ft_strcat(exp, var_value);
		start = end;
		dollar = ft_strchr(start, '$');
	}
	ft_strcat(exp, start);
	free(name);
	return exp;
}

