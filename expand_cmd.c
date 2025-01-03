/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 04:57:34 by mkimdil           #+#    #+#             */
/*   Updated: 2024/08/11 04:44:20 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_quote(t_expand *exp, int *j)
{
	(*j)++;
	while (exp->current[*j] && exp->current[*j] != '\'')
		noex_single(exp, j);
	(*j)++;
}

void	handle_double_quote(t_expand *exp, int *j, t_cmd *lst, t_list *envp)
{
	char	*temp;
	int		k;

	if (exp->current[*j] == '"')
		(*j)++;
	temp = NULL;
	if (exp->current[*j] == '$' && special_case(exp->current[*j + 1]))
	{
		(1) && ((*j)++, k = *j, 0);
		while (exp->current[*j] && special_case(exp->current[*j]))
			(*j)++;
		exp->name = ft_substr(exp->current, k, *j - k);
		exp->value = get_env_value_2(exp->name, envp->envs);
		(1) && (temp = exp->cmd, free(exp->name), 0);
		(1) && (exp->cmd = ft_strjoin(temp, exp->value), free(temp), 0);
	}
	else if (exp->current[*j] == '$' && is_number(exp->current[*j + 1]))
	{
		if (exp->current[*j + 1])
			(*j)++;
		numeric_expand(lst, exp, j);
	}
	if (exp->current[*j] == '"')
		(*j)++;
}

void	numeric_expand(t_cmd *lst, t_expand *exp, int *j)
{
	char	*temp1;

	(*j)++;
	lst->ambiguous = 1;
	temp1 = exp->cmd;
	exp->cmd = ft_strjoin(exp->cmd, NULL);
	free(temp1);
}

void	handle_special_case(t_expand *exp, int *j, t_cmd *lst, t_list *envp)
{
	char	*temp;
	int		k;

	temp = NULL;
	(*j)++;
	if (exp->current[*j] && is_number(exp->current[*j]))
		numeric_expand(lst, exp, j);
	else
	{
		k = *j;
		while (exp->current[*j] && special_case(exp->current[*j]))
			(*j)++;
		exp->name = ft_substr(exp->current, k, *j - k);
		exp->value = get_env_value(exp->name, envp->envs);
		free(exp->name);
		temp = exp->cmd;
		exp->cmd = ft_strjoin(temp, exp->value);
		free(temp);
	}
}

char	*expand_cmd(t_cmd *lst, t_list *envp, int i)
{
	t_expand	exp;
	int			j;
	int			k;

	(1) && (exp.cmd = NULL, exp.current = lst->argv[i], j = 0, k = 0, 0);
	if (lst->fl1 == 1)
		return (expand_export(lst, envp, i));
	while (exp.current[j])
	{
		if (exp.current[j] == '$' && exp.current[j + 1] == '?')
			j++;
		else if (exp.current[j] == '\'')
			handle_single_quote(&exp, &j);
		else if (exp.current[j] == '"')
			handle_double_quote(&exp, &j, lst, envp);
		else if (exp.current[j] == '$' && expand_cases(exp.current[j + 1]))
			handle_special_case(&exp, &j, lst, envp);
		else if (exp.current[j] == '$' && exp.current[j + 1] == '$')
			dolar_dolar_case(&exp, &j);
		else if (exp.current[j] == '$' && exp.current[j + 1] == '"')
			j++;
		else
			last_case(&exp, &j);
	}
	return (exp.cmd);
}
