/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:58:20 by mkimdil           #+#    #+#             */
/*   Updated: 2024/05/16 17:03:25 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syn_error3(char **res)
{
	if (!ft_strncmp(res[0], ">", 2) && !ft_strncmp(res[1], "|", 1))
		printf("bash: syntax error near unexpected token `|'\n");
	else if (!ft_strncmp(res[0], ">", 2) && !ft_strncmp(res[1], "<<", 2))
		printf("bash: syntax error near unexpected token `<<'\n");
	else if (!ft_strncmp(res[0], ">", 2) && !ft_strncmp(res[1], "<", 1))
		printf("bash: syntax error near unexpected token `<'\n");
	else if (!ft_strncmp(res[0], ">", 2) && !ft_strncmp(res[1], ">>", 2))
		printf("bash: syntax error near unexpected token `>>'\n");
	else if (!ft_strncmp(res[0], ">", 2) && !ft_strncmp(res[1], ">", 1))
		printf("bash: syntax error near unexpected token `>'\n");
	free_array(res);
}

void	syn_error2(char **res)
{
	if (**res == '|')
		printf("bash: syntax error near unexpected token `|'\n");
	if (!ft_strncmp(res[0], "<", 2) && !ft_strncmp(res[1], "|", 1))
		printf("bash: syntax error near unexpected token `|'\n");
	else if (!ft_strncmp(res[0], "<", 2) && !ft_strncmp(res[1], "<<", 2))
		printf("bash: syntax error near unexpected token `<<'\n");
	else if (!ft_strncmp(res[0], "<", 2) && !ft_strncmp(res[1], "<", 1))
		printf("bash: syntax error near unexpected token `<'\n");
	else if (!ft_strncmp(res[0], "<", 2) && !ft_strncmp(res[1], ">>", 2))
		printf("bash: syntax error near unexpected token `>>'\n");
	else if (!ft_strncmp(res[0], "<", 2) && !ft_strncmp(res[1], ">", 1))
		printf("bash: syntax error near unexpected token `>'\n");
	else if (!ft_strncmp(res[0], ">>", 3) && !ft_strncmp(res[1], "|", 1))
		printf("bash: syntax error near unexpected token `|'\n");
	else if (!ft_strncmp(res[0], ">>", 3) && !ft_strncmp(res[1], ">", 1))
		printf("bash: syntax error near unexpected token `>'\n");
	else if (!ft_strncmp(res[0], ">>", 3) && !ft_strncmp(res[1], ">>", 2))
		printf("bash: syntax error near unexpected token `>>'\n");
	else if (!ft_strncmp(res[0], ">>", 3) && !ft_strncmp(res[1], "<", 1))
		printf("bash: syntax error near unexpected token `<'\n");
	else if (!ft_strncmp(res[0], ">>", 3) && !ft_strncmp(res[1], "<<", 2))
		printf("bash: syntax error near unexpected token `<<'\n");
	syn_error3(res);
}

void	syn_error(char *line)
{
	char	**res;
	char	*search;

	res = ft_split(line, ' ');
	if (!res || !*res)
		return ;
	if ((!ft_strncmp(res[0], "<<", 3) || !ft_strncmp(res[0], ">>", 3)
			|| !ft_strncmp(res[0], "<", 2) || !ft_strncmp(res[0], ">", 2))
		&& !*(res + 1))
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return ;
	}
	else if (ft_strncmp(*res, "<<", 3) == 0
		&& (!*(res + 1) || res[1][0] == '|'))
		printf("bash: syntax error near unexpected token `|'\n");
	else if (ft_strncmp(*res, "<<", 3) == 0 && ft_strncmp(res[1], "<<", 2) == 0)
		printf("bash: syntax error near unexpected token `<<'\n");
	else if (ft_strncmp(*res, "<<", 3) == 0 && ft_strncmp(res[1], "<", 1) == 0)
		printf("bash: syntax error near unexpected token `<'\n");
	else if (ft_strncmp(*res, "<<", 3) == 0 && ft_strncmp(res[1], ">>", 2) == 0)
		printf("bash: syntax error near unexpected token `>>'\n");
	else if (ft_strncmp(*res, "<<", 3) == 0 && ft_strncmp(res[1], ">", 1) == 0)
		printf("bash: syntax error near unexpected token `>'\n");
	syn_error2(res);
}

void	parsing(char *line)
{
	syn_error(line);
}
