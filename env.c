/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:03:27 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/17 21:25:44 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_split(char *s, char c)
{
	char	**result;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * 3);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && s[i] != c)
		i++;
	result[0] = (char *)malloc(sizeof(char) * (i + 1));
	if (!result[0])
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		result[0][i] = s[i];
		i++;
	}
	result[0][i] = '\0';
	if (s[i])
	{
		result[1] = ft_strdup(s + i + 1);
		if (!result[1])
			return (NULL);
	}
	else
		result[1] = NULL;
	result[2] = NULL;
	return (result);
}

t_env	*env_init(char **envp)
{
	t_env	*head;
	int		i;
	char	**sp;
	t_env	*new;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		sp = env_split(envp[i], '=');
		if (!sp)
			break ;
		if (sp[1] != NULL)
		{
			new = ft_lstnew(sp[0], sp[1]);
			if (new == NULL)
				break ;
			ft_lstadd_back(&head, new);
		}
		i++;
	}
	return (head);
}

void	env(char **argv, t_list *list, int outfile)
{
	t_env	*env;

	env = list->envs;
	while (env)
	{
		if (env->value)
		{
			write(outfile, env->name, ft_strlen(env->name));
			write(outfile, "=", 1);
			write(outfile, env->value, ft_strlen(env->value));
			write(outfile, "\n", 1);
		}
		env = env->next;
	}
}
