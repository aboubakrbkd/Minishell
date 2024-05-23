/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:16:45 by mkimdil           #+#    #+#             */
/*   Updated: 2024/05/23 15:48:52 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

int	special_case(char c)
{
	if (is_ascii(c) || is_number(c) || c == '_')
		return (1);
	return (0);
}

char	*ft_substr(char *s, int start, int len)
{
	int	i;
	int	size;
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

char	*expand_cmd(t_cmd *lst, char **envp, int i, int tr)
{
	char	**splited;
	t_env	*env;
	char	*cmd;
	char	*ptr;
	char	*temp;
	int		j;
	int		r;

	splited = ft_split(lst->argv[i], '$');
	j = 0;
	cmd = ft_strdup("");
	if (!tr)
		cmd = ft_strjoin(cmd, splited[0]);
	while (splited[j])
	{
		r = 0;
		temp = calloc(ft_strlen(splited[j]) + 1, 1);
		i = 0;
		while (splited[j][i])
		{
			if (!special_case(splited[j][i]))	
			{
				temp[r++] = splited[j][i++];
				continue ;
			}
			i++;
		}
		ptr = ft_substr(splited[j], 0, i - r);
		i = 0;
		env = env_init(envp);
		if (!env)
			return (NULL);
		while (env)
		{
			if (ft_strcmp(ptr, env->name) == 0)
				cmd = ft_strjoin(cmd, env->value);
			env = env->next;
		}
		if (temp)
			cmd = ft_strjoin(cmd, temp);
		j++;
	}
	return (cmd);
}

void	expand(t_cmd *lst, char **envp)
{
	t_env	*envir;
	int		i;
	int		tr;

	envir = env_init(envp);
	tr = 0;
	while (lst)
	{
		i = 0;
		while (lst->argv[i])
		{
			if (ft_strchr(lst->argv[i], '$'))
			{
				if (lst->argv[i][0] == '$')
					tr = 1;
				lst->argv[i] = expand_cmd(lst, envp, i, tr);
			}
			i++;
		}
		lst = lst->next;
	}
}
