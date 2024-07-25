/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:20:55 by aboukdid          #+#    #+#             */
/*   Updated: 2024/07/22 22:51:15 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*my_getenv(char *name, t_list *list)
{
	t_env	*env;

	env = list->envs;
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	update_env(char *name, char *value, t_list *list)
{
	t_env	*tmp;

	tmp = list->envs;
	if (!name || !value)
		return ;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name)))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			break ;
		}
		tmp = tmp->next;
	}
}

void	update_pwd(t_list *list)
{
	char	*home;

	update_env("OLDPWD", my_getenv("PWD", list), list);
	home = getcwd(NULL, 0);
	update_env("PWD", home, list);
	free(home);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	int		size;
	char	*ptr;

	if (!s || start >= ft_strlen(s))
	{
		ptr = (char *)malloc(1);
		if (ptr)
			ptr[0] = '\0';
		return (ptr);
	}
	size = 0;
	while (s[start + size] != '\0' && size < len)
		size++;
	ptr = (char *)malloc(size + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[start + i] && i < size)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
