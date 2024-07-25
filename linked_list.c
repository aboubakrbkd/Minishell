/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:25:47 by aboukdid          #+#    #+#             */
/*   Updated: 2024/07/24 23:46:24 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

t_exp	*ft_new_node(char *str)
{
	t_exp	*new;

	new = malloc(sizeof(t_exp));
	if (new)
	{
		new->splited = ft_split(str, ' ');
		new->next = NULL;
	}
	return (new);
}

t_exp	*last_node(t_exp *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_add_back(t_exp **lst, t_exp *new)
{
	t_exp	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = last_node(*lst);
		last->next = new;
	}
}
