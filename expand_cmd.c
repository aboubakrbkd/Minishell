/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 04:57:34 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/25 01:15:52 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_handle_other_cases(t_expand *exp, int *j, int flag)
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
			ft_handle_other_cases(&exp, &j, 0);
		else if (exp.current[j] == '$' && exp.current[j + 1] == '"')
			ft_handle_other_cases(&exp, &j, 1);
		else
			ft_handle_other_cases(&exp, &j, 2);
	}
	return (exp.cmd);
}
