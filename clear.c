/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 01:18:26 by mkimdil           #+#    #+#             */
/*   Updated: 2024/08/07 04:29:12 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arglen(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

char	**append(char **arg, char *expanded, int index)
{
	int		i;
	int		arg_len;
	int		arg2_len;
	char	**new_arg;
	char	**arg2;

	arg2 = ft_split_2(expanded);
	arg_len = arglen(arg);
	arg2_len = arglen(arg2);
	new_arg = malloc(sizeof(char *) * (arg_len + arg2_len - 1 + 1 + 1000));
	if (!new_arg)
		return (NULL);
	i = 0;
	while (i < index)
	{
		new_arg[i] = arg[i];
		i++;
	}
	int j = 0;
	while (j < arg2_len)
	{
		new_arg[i] = arg2[j];
		i++;
		j++;
	}
	while (index < arg_len - 1)
	{
		new_arg[i] = arg[index + 1];
		index++;
		i++;
	}
	new_arg[i] = NULL;
	return new_arg;
}

// char	**join_args_help(char **s1, char **splited, char **res, int i)
// {
// 	int		j;
// 	int		k;

// 	j = 0;
// 	k = i;
// 	while (splited[j])
// 	{
// 		res[k] = ft_strdup(splited[j]);
// 		if (!res[k])
// 			return (fr(res), fr(splited), NULL);
// 		j++;
// 		k++;
// 	}
// 	i++;
// 	while (s1[i])
// 	{
// 		res[k] = ft_strdup(s1[i]);
// 		k++;
// 		i++;
// 	}
// 	res[k] = NULL;
// 	return (fr(s1), fr(splited), res);
// }

// char	**join_args(char **s1, char *expanded)
// {
// 	char	**res;
// 	char	**splited;
// 	int		i;

// 	splited = ft_split_2(expanded);
// 	res = malloc((10000) * sizeof(char *));
// 	if (!splited || !res)
// 		return (fr(splited), free(res), NULL);
// 	i = 0;
// 	while (s1[i] && !ft_strchr(s1[i], '$'))
// 	{
// 		res[i] = ft_strdup(s1[i]);
// 		if (!res[i])
// 			return (fr(res), fr(splited), NULL);
// 		i++;
// 	}
// 	return (join_args_help(s1, splited, res, i));
// }

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
