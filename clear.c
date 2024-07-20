/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 01:18:26 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/20 07:02:23 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_quotes(char *input)
{
	int		count;
	int		i;
	char	quote;

	i = -1;
	count = 0;
	while (input[++i])
		if (input[i] == '\'' || input[i] == '"')
			quote = input[i];
	i = -1;
	while (input[++i])
	{
		if (input[i] == quote)
		{
			count++;
			continue ;
		}
	}
	return (count);
}

char	*unquote(char* input)
{
	int		len;
	int		i;
	int		in_single_quote;
	int		in_double_quote;
	char	*result;
	char	*p;

	if (count_quotes(input) == 2)
		return (input);
	len = ft_strlen(input);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	p = result;
    in_single_quote = 0;
    in_double_quote = 0;
	i = -1;
	while (++i < len)
	{
		if (input[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else
			*p++ = input[i];
	}
	*p = '\0';
	return (result);
}
