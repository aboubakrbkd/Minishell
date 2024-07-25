/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 23:12:08 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/25 00:58:09 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc(ft_strlen(str) + 1);
	if (!ptr)
		return (NULL);
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	countword(char *s, char c)
{
	int	count;

	count = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s && (*s != c))
				s++;
		}
		else
			s++;
	}
	return (count);
}

char	*ft_strndup(char *src, int n)
{
	int		i;
	char	*result;

	result = (char *)malloc(n + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		result[i] = src[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

void	ft_free(char **ptr, int i)
{
	while (i >= 0)
	{
		free(ptr[i]);
		i--;
	}
	free(ptr);
}

char	**ft_help(char *s, char c, int len, char **final)
{
	char	*start;
	int		i;

	len = countword(s, c);
	final = (char **)malloc((len + 1) * sizeof(char *));
	if (!final)
		return (NULL);
	i = 0;
	while (i < len)
	{
		while (*s == c)
			s++;
		start = (char *)s;
		while (*s && *s != c)
			s++;
		final[i] = ft_strndup(start, s - start);
		if (!final[i])
		{
			ft_free(final, i);
			return (NULL);
		}
		i++;
	}
	final[i] = NULL;
	return (final);
}

char	**ft_split(char *s, char c)
{
	int		len;
	char	**final;

	final = NULL;
	len = 0;
	return (ft_help(s, c, len, final));
}
t_cmd	*ft_new(char *cmd)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	if (new)
	{
		new->cmd = ft_strdup(cmd);
		if (!new->cmd)
			return (NULL);
		new->argv = ft_split(new->cmd, ' ');
		if (!new->argv)
			return (NULL);
		new->infile = 0;
		new->outfile = 1;
		new->ambiguous = 0;
		new->in_quote = -1;
		new->is_heredoc = -1;
		new->next = NULL;
	}
	return (new);
}

t_cmd	*get_last(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = get_last(*lst);
		last->next = new;
	}
}

t_cmd	*build_arr(char **res)
{
	t_cmd	*head;
	int		i;

	head = NULL;
	i = 0;
	while (res[i])
	{
		add_back(&head, ft_new(res[i]));
		i++;
	}
	return (head);
}

typedef struct s_list
{
	int		tr;
	int		argv_size;
	char	**splited;
	char	*expanded;
	char	*tmp;
	t_env	*envs;
}				t_list;

void	expand_with_space(t_cmd *lst, t_list *envp, int	*i)
{
	int	j;
	int	k;

	lst->ambiguous = 1;
	envp->splited = ft_split(envp->expanded, ' ');
	envp->argv_size = 0;
	while (lst->argv[envp->argv_size])
		envp->argv_size++;
	j = 0;
	while (envp->splited[j])
		(j)++;
	k = envp->argv_size;
	while (k >= *i)
	{
		lst->argv[k - j - 1] = lst->argv[k];
		k--;
	}
	j = 0;
	k = *i;
	while (envp->splited[j])
	{
		lst->argv[k] = ft_strdup(envp->splited[j]);
		k++;
		j++;
	}
}

void	expand_without_space(t_cmd *lst, t_list *envp, int *i)
{
	lst->argv[*i] = ft_strdup(envp->expanded);
	if (ft_strlen(envp->expanded) == 0 && lst->ambiguous == 0)
	{
		if (envp->tr != 1 && envp->tr != 2)
			lst->ambiguous = 1;
		lst->argv[*i] = NULL;
	}
}

void	expand_helper(t_cmd *lst, t_list *envp, int *i)
{
	if (ft_strsearch(lst->argv[*i], '"'))
		envp->tr = 1;
	if (ft_strsearch(lst->argv[*i], '\''))
		envp->tr = 2;
	if (envp->tr == 1 || envp->tr == 0)
	{
		envp->expanded = expand_cmd(lst, envp, *i);
		if (ft_strsearch(envp->expanded, ' ') && envp->tr == 0)
			expand_with_space(lst, envp, i);
		else
			expand_without_space(lst, envp, i);
	}
}

void	expand(t_cmd *lst, t_list *envp)
{
	int	i;

	envp->tr = 0;
	while (lst)
	{
		i = 0;
		while (lst->argv[i])
		{
			if (ft_strchr(lst->argv[i], '$') && lst->argv[i + 1]
				&& !ft_strchr(lst->argv[i + 1], '$'))
					envp->tmp = lst->argv[i + 1];
			if (ft_strchr(lst->argv[i], '$'))
				expand_helper(lst, envp, &i);
			if (envp->tmp && !lst->argv[i])
				lst->argv[i] = ft_strdup(envp->tmp);
			i++;
		}
		lst = lst->next;
	}
}

typedef struct s_expand
{
	char	*cmd;
	char	*current;
	char	*var_name;
	char	*value;
}	t_expand;

void	single_quote(t_expand *exp, int *j)
{
	(*j)++;
	while (exp->current[(*j)] && exp->current[(*j)] != '\'')
	{
		exp->cmd = ft_strjoin(exp->cmd, ft_substr(exp->current, (*j), 1));
		(*j)++;
	}
	if (exp->current[(*j)] == '\'')
		(*j)++;
}

void	double_quote(t_expand *exp, int *j, int *k, t_list *envp)
{
	(*j)++;
	while (exp->current[(*j)] && exp->current[(*j)] != '"')
	{
		if (exp->current[(*j)] == '$' && special_case(exp->current[(*j) + 1]))
		{
			(*j)++;
			(*k) = (*j);
			while (exp->current[(*j)] && special_case(exp->current[(*j)]))
				(*j)++;
			exp->var_name = ft_substr(exp->current, (*k), (*j) - (*k));
			exp->value = get_env_value(exp->var_name, envp->envs);
			exp->cmd = ft_strjoin(exp->cmd, exp->value);
			free(exp->var_name);
		}
		else
		{
			exp->cmd = ft_strjoin(exp->cmd, ft_substr(exp->current, (*j), 1));
			(*j)++;
		}
	}
	if (exp->current[(*j)] == '"')
		(*j)++;
}

void	handle_spetial_case(t_expand *exp, int *j, int *k, t_list *envp)
{
	(*j)++;
	(*k) = (*j);
	while (exp->current[(*j)] && special_case(exp->current[(*j)]))
		(*j)++;
	exp->var_name = ft_substr(exp->current, (*k), (*j) - (*k));
	exp->value = get_env_value(exp->var_name, envp->envs);
	exp->cmd = ft_strjoin(exp->cmd, exp->value);
	free(exp->var_name);
}

void	handle_other_cases(t_expand *exp, int *j, int flag)
{
	if (flag == 0)
		(*j) += 2;
	else if (flag == 1)
		(*j)++;
	else if (flag == 2)
	{
		exp->cmd = ft_strjoin(exp->cmd, ft_substr(exp->current, *j, 1));
		(*j)++;
	}
}

char	*expand_cmd(t_cmd *lst, t_list *envp, int i)
{
	t_expand	exp;
	int			j;
	int			k;

	exp.cmd = ft_strdup("");
	exp.current = lst->argv[i];
	j = 0;
	while (exp.current[j])
	{
		if (exp.current[j] == '$' && exp.current[j + 1] == '?')
			j++;
		else if (exp.current[j] == '\'')
			single_quote(&exp, &j);
		else if (exp.current[j] == '"')
			double_quote(&exp, &j, &k, envp);
		else if (exp.current[j] == '$' && special_case(exp.current[j + 1]))
			handle_spetial_case(&exp, &j, &k, envp);
		else if (exp.current[j] == '$' && exp.current[j + 1] == '$')
			handle_other_cases(&exp, &j, 0);
		else if (exp.current[j] == '$' && exp.current[j + 1] == '"')
			handle_other_cases(&exp, &j, 1);
		else
			handle_other_cases(&exp, &j, 2);
	}
	return (exp.cmd);
}

int main(void)
{
	char	*strs[] = {"ls -l -a", "cat /dev/urandom",  "head -1", NULL};
	t_cmd	*cmd = build_arr(strs);
	while (cmd)
	{
		int i = 0;
		printf("cmd->cmd: %s\n", cmd->cmd);
		while (cmd->argv[i])
		{
			printf("cmd->argv[%d]: %s\n", i, cmd->argv[i]);
			i++;
		}
		cmd = cmd->next;
	}
	return (0);
}