/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:03:27 by aboukdid          #+#    #+#             */
/*   Updated: 2024/04/16 16:50:24 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// i need to change them to 2d array

t_env	*ft_lstnew(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new)
	{
		new->name = ft_strdup(name);
		new->value = ft_strdup(value);
		new->next = NULL;
	}
	return (new);
}

t_env	*ft_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

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
		new = ft_lstnew(sp[0], sp[1]);
		if (new == NULL)
			break ;
		ft_lstadd_back(&head, new);
		i++;
	}
	return (head);
}

void	env(t_env *env, char **envp)
{
	env = env_init(envp);
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

// void	dynamic_env(char **envp)
// {
// 	int i = 0;
// 	t_env *env = env_init(envp);
// 	char **envr;
// 	while (env)
// 	{
// 		i++;
// 		env = env->next;
// 	}
// 	envr = malloc(sizeof(char *) * (i + 1));
// 	i = 0;
// 	while (env)
// 	{
// 		envr = ft_strjoin(env->name, "=");
// 		envr = ft_strjoin(envr, env->value);
// 		i++;
// 	}
// 	envr[i] = NULL;
// }
// int main(int argc, char **argv, char **envp)
// {
// 	t_env *envm;
// 	env(envm, envp);
// }
