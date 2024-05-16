/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:20:55 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/15 20:12:01 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*my_getenv(char *name)
{
	t_env	*env;

	env = g_global.envs;
	while (env)
	{
		if (!ft_strncmp(env->name, name, ft_strlen(name)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	update_env(char *name, char *value)
{
	t_env	*tmp;

	tmp = g_global.envs;
	if (!name || !value)
		return ;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name)))
		{
			tmp->value = ft_strdup(value);
			break ;
		}
		tmp = tmp->next;
	}
}

void	update_pwd(char *path)
{
	char	*home;

	update_env("OLDPWD", my_getenv("PWD"));
	home = getcwd(NULL, 0);
	update_env("PWD", home);
}
