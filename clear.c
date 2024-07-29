/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 01:18:26 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/29 00:56:24 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**join_args_help(char **s1, char **splited, char **res, int i)
{
	int		j;
	int		k;

	j = -1;
	while (splited[++j])
	{
		res[i] = strdup(splited[j]);
		if (!res[i])
			return (free_all(res), free_all(splited), NULL);
		i++;
	}
	k = -1;
	while (s1[i + (++k)])
	{
		res[i + k] = strdup(s1[i + k]);
		if (!res[i + k])
			return (free_all(res), free_all(splited), NULL);
	}
	res[i + k] = NULL;
	return (free_all(splited), res);
}

char	**join_args(char **s1, char *expanded)
{
	char	**res;
	char	**splited;
	int		i;

	splited = ft_split(expanded, ' ');
	res = malloc((args_len(s1) + args_len(splited) + 1) * sizeof(char *));
	if (!splited || !res)
		return (free_all(splited), free(res), NULL);
	i = -1;
	while (s1[++i] && !ft_strchr(s1[i], '$'))
	{
		res[i] = strdup(s1[i]);
		if (!res[i])
			return (free_all(res), free_all(splited), NULL);
	}
	return (join_args_help(s1, splited, res, i));
}

int	count_single(char *input)
{
	int		count;
	int		i;
	char	quote;

	i = -1;
	count = 0;
	quote = '\'';
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

int	count_double(char *input)
{
	int		count;
	int		i;
	char	quote;

	i = -1;
	count = 0;
	quote = '\"';
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

char	*unquote(char	*input)
{
	t_expand	unq;
	int			i;
	char		*result;
	char		*p;

	unq.len = ft_strlen(input);
	result = malloc(unq.len + 1);
	if (!result)
		return (NULL);
	p = result;
	unq.in_single_quote = 0;
	unq.in_double_quote = 0;
	i = -1;
	while (++i < unq.len)
	{
		if (input[i] == '\'' && !unq.in_double_quote)
			unq.in_single_quote = !unq.in_single_quote;
		else if (input[i] == '"' && !unq.in_single_quote)
			unq.in_double_quote = !unq.in_double_quote;
		else
			*p++ = input[i];
	}
	*p = '\0';
	return (result);
}
