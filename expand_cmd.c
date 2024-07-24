/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 04:57:34 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/25 00:33:32 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *var_name, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(var_name, env->name) == 0)
			return (env->value);
		env = env->next;
	}
	return ("");
}

char	*expand_cmd(t_cmd *lst, t_list *envp, int i)
{
	char	*cmd;
	char	*current;
	char	*var_name;
	char	*value;
	int		j;
	int		k;

	cmd = ft_strdup("");
	current = lst->argv[i];
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
