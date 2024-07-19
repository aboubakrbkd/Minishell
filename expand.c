/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:16:45 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/19 03:56:21 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_case(char c)
{
	return (is_ascii(c) || is_number(c) || c == '_');
}

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

// char	**handle_expand(t_cmd *lst)
// {
// 	t_exp	*cmd;
// 	t_exp	*head;
// 	char	**str;
// 	int		i;
// 	int		j;

// 	head = NULL;
// 	cmd = NULL;
// 	i = -1;
// 	while (lst->argv[++i])
// 		if (ft_strchr(lst->argv[i], ' '))
// 			ft_add_back(&head, ft_new_node(lst->argv[i]));
// 	str = malloc(sizeof(char *) * 1000);
// 	i = 0;
// 	cmd = head;
// 	while (cmd)
// 	{
// 		j = -1;
// 		while (cmd->splited[++j])
// 		{
// 			str[i] = cmd->splited[j];
// 			i++;
// 		}
// 		cmd = cmd->next;
// 	}
// 	i = 0;
// 	while (str[i])
// 	{
// 		printf("str[%d]: %s\n", i, str[i]);
// 		i++;
// 	}
// 	str[i] = NULL;
// 	return (str);
// }

void	expand(t_cmd *lst, t_list *envp)
{
	int		i;

	while (lst)
	{
		i = 0;
		while (lst->argv[i])
		{
			if (ft_strchr(lst->argv[i], '$'))
			{
				lst->argv[i] = expand_cmd(lst, envp, i);
				if (ft_strsearch(lst->argv[i], ' '))
					append_it(lst, &i);
			}
			i++;
		}
		i = 0;
		while (lst->argv[i])
		{
			if (ft_strchr(lst->argv[i], ' '))
				print_args(lst);
			i++;
		}
		// 	lst->argv = handle_expand(lst);
		lst = lst->next;
	}
}
