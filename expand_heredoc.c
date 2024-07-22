/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 01:37:05 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/22 06:14:56 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_here_cmd(char *temp, t_list *envp)
{
	char	*cmd;
	char	*current;
	char	*var_name;
	char	*value;
	int		j;
	int		k;

	cmd = ft_strdup("");
	current = temp;
	j = 0;
	while (current[j])
	{
		if (current[j] == '$' && current[j + 1] == '?')
			j++;
		else if (current[j] == '\'')
		{
			j++;
			while (current[j] && current[j] != '\'')
			{
				cmd = ft_strjoin(cmd, ft_substr(current, j, 1));
				j++;
			}
			if (current[j] == '\'')
				j++;
		}
		else if (current[j] == '"')
		{
			j++;
			while (current[j] && current[j] != '"')
			{
				if (current[j] == '$' && special_case(current[j + 1]))
				{
					j++;
					k = j;
					while (current[j] && special_case(current[j]))
						j++;
					var_name = ft_substr(current, k, j - k);
					value = get_env_value(var_name, envp->envs);
					cmd = ft_strjoin(cmd, value);
					free(var_name);
				}
				else
				{
					cmd = ft_strjoin(cmd, ft_substr(current, j, 1));
					j++;
				}
			}
			if (current[j] == '"')
				j++;
		}
		else if (current[j] == '$' && special_case(current[j + 1]))
		{
			j++;
			k = j;
			while (current[j] && special_case(current[j]))
				j++;
			var_name = ft_substr(current, k, j - k);
			value = get_env_value(var_name, envp->envs);
			cmd = ft_strjoin(cmd, value);
			free(var_name);
		}
		else if (current[j] == '$' && current[j + 1] == '$')
			j += 2;
		else if (current[j] == '$' && current[j + 1] == '"')
			j++;
		else
		{
			cmd = ft_strjoin(cmd, ft_substr(current, j, 1));
			j++;
		}
	}
	return (cmd);
}

char	*expand_heredoc(char *temp, t_list *envp)
{
	char	*expanded;

	expanded = NULL;
	if (ft_strchr(temp, '$'))
		expanded = expand_here_cmd(temp, envp);
	if (!expanded)
		expanded = temp;
	return (expanded);
}
